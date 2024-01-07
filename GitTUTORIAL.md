# GIT

## What is Git :
it’s a version control system ; a version control system it’s a system that help us track our code with every change we make in it; which make debugging and team work easier ; 

And GITHUB is an online platform where u can use GIT.

## Verify that git had succefuly instaled : 
git --version 
or 
git version X.Y

//if it is veryfied it will show : git version 2.30.2.windows.1 // ur current version 

## Configure Git 
git config --global user.name "user name"
git config --global user.email "e mail"

//using global is to use this username and email in every repo in ur computer
remove global to use them in this repo only

## Creating Git Folder
mkdir myproject //makes new directory 
cd myproject // go to this directory we montioned

## Initialize Git
git init 

// it will show : Initialized empty Git repository in /Users/user/myproject/.git/

## Git Adding New Files
// create ur file in ur favorite ide and fav lang

ls // list ur project in ur directory

// it will show :
project.c 

ls -la // show everything including hiding files // abbr : la

// to see that it has been list, use the following code : 
git status

// it will show : 
On branch master

No commits yet

Untracked files:
  (use "git add ..." to include in what will be committed)
    project.c 

nothing added to commit but untracked files present (use "git add" to track)

// now git is aware of the file but did not added to our repo = Untracked files

## Git Staging
//  files that are ready to be committed to the repository

git add project.c // staging the file

git status // verefying our sraged file 
// it shows
On branch master

No commits yet
git add --all // or git add .
Changes to be committed:
  (use "git rm --cached ..." to unstage)
    new file: project.c

// Add More than One File : 
git add --all 
or  
git add -A

## Git Commit 
// = save file = tracked file // git commit
// when we commit we should always leave a message // -m

git commit -m "Added project.c" -m "Some description" 

// The Staging Environment has been committed to our repo, with the message:
"First release of Hello World!"

git status --short //changes in a more compact way

//meeaning of short statuts
?? - Untracked files
A - Files added to stage
M - Modified files
D - Deleted files


git commit -a -m "Updated projet.c with a new line" //  commit without staging for brief changes


git log //To view the history of commits for a repository

## Git Branch
// is to used when we want to modify the  code without impecting the main code


git branch project-branch // we creted a branch of our project

// confirm we have created the  branch :
git branch //to see all the branches you have

// it will show : 
 project-branch
* master // specifies that we are currently on that branch

git checkout project-branch //to switch from a branch to branch

// it will show : Switched to branch 'project-branch'

git checkout -b project-branch1 //to create new branch and switch to it

## clone 
// bring repository hosted in a online platform like git hub to ur local machine.

push —> ulpoad git files in a remote repositry like github.
pull —> download changes from online repo to ur local machine the opposite of push

