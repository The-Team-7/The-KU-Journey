Just copy these three files inside the main Game folder and rename them to following:

Game.vcxproj
Game.vcxproj.filters
Game.vcxproj.user

They are vsstudio project files and settings files. Since each of the team member has different
system and project settings, it is important for each of us to manually make the settings for
librairies. Since git detects the change while commiting. It would be ambigious if each of us have
different project settings in our local git repo. So to prevent that we are ignoring these specific
files , i.e preventing these files from being tracked from git. So just copy them manually into
the Game folder and change the name. So that even if we change our settings in local repo,
it wont get reflected in the main git repository.

