### Git Workflow

In order to effectively collaborate, we will be utilizing 'feature' branches and 'pull-requests'
The idea is that, our GitLab board will have numbered 'issues' with tasks outlined in them.
Members of the group will be assigned to work on those tickets
To work on a feature in isolation, you will need to branch off the master branch, and name your branch feat/#{issue_number}-some-description-of-the-issue

Commit and push all work for that feature to that branch
When you are ready to have the code reviewed and merged back into the master branch, you will open a pull request and tag the team as code reviewers

More information: https://www.atlassian.com/git/tutorials/comparing-workflows/feature-branch-workflow

### Creating Branches

`git checkout -b feat/#1-example-branch-with-example-ticket`

### Committing

`git commit -am '#1 - Example commit with example ticket number'`

### Pushing

Normally you can simply `git push` after making a commit, being sure that you are on your _own_ feature branch. However, typically a brand new branch needs an extra flag to set the remote branch to track the local branch

`git push --set-upstream origin feat/#1-example-branch-with-example-ticket`


