ASCII Obfuscation
=================

This is a small example program to show / have fun with `ASCII` characters and the way we can easily obfuscate them

Miscealeanous :
---------------

[Where](./documentation/blog/small_talk.md) such a dumb idea comes from.

[Coding rules](./documentation/blog/coding_style.md) used in this project.

Source code [Online documentation](./documentation/html/index.html).

Repository content :
--------------------

- **.git** : _GIT_ version control files. **DO NOT EDIT** unless you know precisely what you're doing.
- **sources** : Project source files directory. The final binary file will be compiled from these source code files.
- **project** : This directory contains IDE related project files. Only [Code::Blocks](http://www.codeblocks.org/) is used at the moment
- **documentation** : Documentation directory.
  - **blog** : _Markdow_ files used for Jekyll blog posts.
  - **html** : [_HTML Doxygen_](http://www.stack.nl/~dimitri/doxygen/manual/starting.html#html_out) generated documentation directory. Used for online documentation.
  - **pdf** : Contains a pdf file genrated using [_LaTeX output from Doxygen_](http://www.stack.nl/~dimitri/doxygen/manual/starting.html#latex_out).
  - _ascii_obfuscation.doxygen.cnfg_ : [_Doxygen_](http://www.stack.nl/~dimitri/doxygen/index.html) configuration file
  - _generdoc.bat_ : _MicroSoft Windows_ ```.bat``` script used to automatically generate the _Doxygen_ documentation. Double-click on this to generate the documentation.<br>
    _IMPORTANT :_ You should have the *Ubuntu* subsytem with _Doxygen_ installed on your computer in order to use this script.
- _.gitignore_ : _GIT_ ignore file. This allows us to exclude automatically generated files and directory from the project
- __config.yml_ : _Jekyll_ configuration file
- _LICENSE_ : Project licence file. [_GNU GPL3_](https://www.gnu.org/licenses/gpl-3.0.html) is used here.
- _README.md_ : This file.
