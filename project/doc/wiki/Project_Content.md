PROJECT CONTENT
===============
8-Bit Hubble project contains a wiki (ahem), an issue tracker, and two main branches: master and development. The creation of two
branches follows [this approach](https://nvie.com/posts/a-successful-git-branching-model/).

The project content is organized in the following [5S Methodology](https://en.wikipedia.org/wiki/5S_(methodology)) directory hierarchy. 
The goal is to provide a directory structure that is easy to follow and where "everything has a place, and there is a place for everything".

![8-Bit Hubble_dir_structure](@TODO)

Below, a description of each folder:

- The **root directory** contains the repository "front end" files: the installation script (setup.sh), the VCS files (README, LICENSE and git files);
as well as the *Project* directory, containing the project data (source code, makefiles, requirements, tests, traceability data, etc.) and the *Download*
directory, with ready-to-go executables aimed to non-developers and casual users.
- **Project** directory is then divided in the main "triforce":
    - **Doc** folder contains all documentation files: media (images, sounds), the wiki pages, and templates (script templates, source code templates).
    - **Scripts** folder contains all scripts used in the project, of any kind and no matter the purpose.
    - **Dev** folder, based in the primal [Waterfall Model](https://en.wikipedia.org/wiki/Waterfall_model). Here is where the "core" of the project
    is found: source code, unit tests, Makefiles, XMLs, coverage reports and so on.
