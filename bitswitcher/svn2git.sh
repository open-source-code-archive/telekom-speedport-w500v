#!/bin/bash
#
# https://danielpocock.com/migrating-a-sourceforge-project-from-subversion-to-git/
#

#set -e
set -x

project="bitswitcher"
svn_repo="https://svn.code.sf.net/p/$project/code"

cwd="$(realpath .)"
svn_dir="$cwd/$project.svn"
authors_transform="$cwd/authors-transform.txt"
git_tmp_dir="$cwd/$project.git-checkout"
git_bare_dir="$cwd/$project.git-bare"

# Clone svn repository
if [ ! -d "$svn_dir" ]; then
  svn checkout "$svn_repo" "$svn_dir" &> svn-checkout.log
fi

# Fetch all commits
cd "$svn_dir"
false || while [ $? != 0 ]; do
  # Try updating the repo until it succeeds
  svn cleanup
  svn update
done

# Author name mapping
if [ ! -f $authors_transform ]; then
  svn log -q | \
  awk -F '|' '/^r/ {sub("^ ", "", $2); sub(" $", "", $2); print $2" = "$2" <"$2">"}' | \
  sort -u > $authors_transform

  vi $authors_transform
fi

# Using git-svn to create a git repository
if [ ! -d "$git_tmp_dir" ]; then
  cd "$cwd"
  git svn clone $svn_repo --no-metadata -A authors-transform.txt --stdlayout $git_tmp_dir &> git-svn-checkout.log
fi

# Create bare git repository
if [ ! -d "$git_bare_dir" ]; then
  mkdir -p "$git_bare_dir"
  cd "$git_bare_dir"
  git init --bare .
  git symbolic-ref HEAD refs/heads/trunk
fi

# Push checkout to bare repo
cd "$git_tmp_dir"
git remote add bare "$git_bare_dir"
git config remote.bare.push 'refs/remotes/*:refs/heads/*'
git push bare

# Convert tags
cd "$git_bare_dir"
git branch -m trunk master
git for-each-ref --format='%(refname)' refs/heads/tags | cut -d / -f 4 | while read ref; do \
  git tag "$ref" "refs/heads/tags/$ref" \
  git branch -D "tags/$ref" \
done

# Push repo with tags to new remote
git remote add origin https://git.bihealth.org/bockm-cicd/oscar/bitswitcher
git config branch.master.remote origin
git config branch.master.merge refs/heads/master
git push --tags origin master

