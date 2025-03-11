.. -*- Mode: rst -*-


Installation
============

.. note::
   As the sources are being released, the binary packaging is dropped.
   You may still find (very) old versions here: http://asim.lip6.fr/pub/coriolis/2.0 .

In a nutshell, building source consists in pulling the |git| repository then
running the |ccb| installer. 

.. note::
   The documentation is already generated and commited in the |git| tree.
   You may not install the additional prerequisites for the documentation.
   By default the documentation is not generated, just installed by |ccb|.
   If you really want to re-generate it, add the ``--doc`` flag to |ccb|.

Main building prerequisites:

* cmake
* C++11-capable compiler
* BFD library (provided through ``binutils``).
* RapidJSON_
* python2.7
* boost
* libxml2
* bzip2
* yacc & lex
* Qt 4 or Qt 5
* PyQt 4 or PyQt 5
* Qwt 6

Building documentation prerequisites:

* doxygen
* latex
* python-docutils (for reStructuredText)
* pelican

The following libraries get directly bundled with |Coriolis|:

* LEF/DEF (from Si2_)
* FLUTE (from `Chris C. N. Chu <http://home.eng.iastate.edu/~cnchu/flute.html>`_)

For other distributions, refer to their own packaging system.


Fixed Directory Tree
~~~~~~~~~~~~~~~~~~~~

In order to simplify the work of the |ccb| installer, the source, build
and installation tree is fixed. To successfully compile |Coriolis| you must
follow it exactly. The tree is relative to the home directory of the user
building it (note :fboxtt:`~/` or :fboxtt:`$HOME/`). Only the source
directory needs to be manually created by the user, all others will be
automatically created either by |ccb| or the build system.

+--------------------------------------------------------------------------------------------------------------+
| **Sources**                                                                                                  |
+------------------------------+-------------------------------------------------------------------------------+
| | Sources root               | | ~/coriolis-2.x/src                                                          |
| | **under git**              | | ~/coriolis-2.x/src/coriolis                                                 |
+------------------------------+-------------------------------------------------------------------------------+
| **Architecture Dependant Build**                                                                             |
+------------------------------+-------------------------------------------------------------------------------+
| | Linux, SL 7, 64b           | | ~/coriolis-2.x/Linux.el7_64/Release.Shared/build/<tool>                     |
| | Linux, SL 6, 32b           | | ~/coriolis-2.x/Linux.slsoc6x/Release.Shared/build/<tool>                    |
| | Linux, SL 6, 64b           | | ~/coriolis-2.x/Linux.slsoc6x_64/Release.Shared/build/<tool>                 |
| | Linux, Fedora, 64b         | | ~/coriolis-2.x/Linux.fc_64/Release.Shared/build/<tool>                      |
| | Linux, Fedora, 32b         | | ~/coriolis-2.x/Linux.fc/Release.Shared/build/<tool>                         |
| | FreeBSD 8, 32b             | | ~/coriolis-2.x/FreeBSD.8x.i386/Release.Shared/build/<tool>                  |
| | FreeBSD 8, 64b             | | ~/coriolis-2.x/FreeBSD.8x.amd64/Release.Shared/build/<tool>                 |
| | Windows 7, 32b             | | ~/coriolis-2.x/Cygwin.W7/Release.Shared/build/<tool>                        |
| | Windows 7, 64b             | | ~/coriolis-2.x/Cygwin.W7_64/Release.Shared/build/<tool>                     |
| | Windows 8.x, 32b           | | ~/coriolis-2.x/Cygwin.W8/Release.Shared/build/<tool>                        |
| | Windows 8.x, 64b           | | ~/coriolis-2.x/Cygwin.W8_64/Release.Shared/build/<tool>                     |
+------------------------------+-------------------------------------------------------------------------------+
| **Architecture Dependant Install**                                                                           |
+------------------------------+-------------------------------------------------------------------------------+
|   Linux, SL 6, 32b           |   ~/coriolis-2.x/Linux.slsoc6x/Release.Shared/install/                        |
+------------------------------+-------------------------------------------------------------------------------+
| **FHS Compliant Structure under Install**                                                                    |
+------------------------------+-------------------------------------------------------------------------------+
| | Binaries                   | | .../install/bin                                                             |
| | Libraries (Python)         | | .../install/lib                                                             |
| | Include by tool            | | .../install/include/coriolis2/<project>/<tool>                              |
| | Configuration files        | | .../install/etc/coriolis2/                                                  |
| | Doc, by tool               | | .../install/share/doc/coriolis2/en/html/<tool>                              |
+------------------------------+-------------------------------------------------------------------------------+

.. note:: *Alternate build types:* the ``Release.Shared`` means an optimized build
   with shared libraries. But there are also available ``Static`` instead of ``Shared``
   and ``Debug`` instead of ``Release`` and any combination of them.

   ``Static`` does not work because I don't know yet to mix statically linked binaries
   and Python modules (which must be dynamic).


Building Coriolis
~~~~~~~~~~~~~~~~~

The actively developed branch
-----------------------------

The **devel_anabatic** branch is now closed and we go back to a more classical
scheme where **master** is the stable version and **devel** the development one.

The |Coriolis| |git| repository is https://github.com/lip6/coriolis.git

.. note::
   Again, the **devel_anabatic** branch is now closed. Please revert to **devel**
   or **master**.

.. note::
   As it is now possible to mix |PyQt| widget with |Coriolis| ones, it is simpler
   for us to revert to |Qt| 4 only. Our reference |OS| being |RHEL| 7, there is no
   compatible |PyQt5| build compatible with their |Qt| 5 version (we fall short of
   one minor, they provides |Qt| 5.9 were we need at least |Qt| 5.10).

.. note::
   Under |RHEL| 7 or clones, they upgraded their version of |Qt| 4 (from 4.6 to 4.8)
   so the *diagonal line* bug no longer occurs. So we can safely use the default
   system |Qt| again.


Installing on |RedHat| or compatible distributions
--------------------------------------------------

1. Install or check that the required prerequisites are installed :

   .. code-block:: bash
 
      dummy@lepka:~> yum install -y git cmake bison flex gcc-c++ libstdc++-devel  \
                                    binutils-devel                                \
                                    boost-devel boost-python boost-filesystem     \
                                    boost-regex  boost-wave                       \
                                    python-devel libxml2-devel bzip2-devel        \
                                    qt-devel 
   
  The packages ``qwt`` and ``qwt-devel`` are not provided by any standard repository
  (like |EPEL|). You may download them from the
  `LIP6 Addons Repository <https://ftp.lip6.fr/pub/linux/distributions/slsoc/soc/7/addons/x86_64/repoview/letter_q.group.html>`_
  Then run:

  .. code-block:: sh
   
     dummy@lepka:~> yum localinstall -y qwt-6.1.2-4.fc23.x86_64.rpm        \
                                        qwt-devel-6.1.2-4.fc23.x86_64.rpm  # Qwt for Qt 4.

  You may also install them directly (whithout an intermediate download):

  .. code-block:: sh
   
     dummy@lepka:~> yum install -y http://ftp.lip6.fr/pub/linux/distributions/slsoc/soc/7/addons/x86_64/RPMS/qwt-6.1.2-4.fc23.x86_64.rpm \
                                   http://ftp.lip6.fr/pub/linux/distributions/slsoc/soc/7/addons/x86_64/RPMS/qwt-devel-6.1.2-4.fc23.x86_64.rpm 

2. Install the unpackaged prerequisites. Currently, only RapidJSON_.

   .. code-block:: sh

      dummy@lepka:~> mkdir -p ~/coriolis-2.x/src/support
      dummy@lepka:support> cd ~/coriolis-2.x/src/support
      dummy@lepka:support> git clone http://github.com/miloyip/rapidjson


3. Create the source directory and pull the |git| repository:

   .. code-block:: sh

      dummy@lepka:~> mkdir -p ~/coriolis-2.x/src
      dummy@lepka:src> cd ~/coriolis-2.x/src
      dummy@lepka:src> git clone https://github.com/lip6/coriolis.git

4. Build & install:

   .. code-block:: sh

      dummy@lepka:src> cd coriolis
      dummy@lepka:coriolis> git checkout devel
      dummy@lepka:coriolis> ./bootstrap/ccb.py --project=support  \
                                               --project=coriolis \
                                               --make="-j4 install"

.. note::
   Pre-generated documentation will get installed by the previous command.
   Only if you did made modifications to it you need to regenerate it with:

   .. code-block:: sh
  
      dummy@lepka:coriolis> ./bootstrap/ccb.py --project=support  \
                                               --project=coriolis \
                                               --doc --make="-j1 install"
    
   We need to perform a separate installation of the documentation because it
   does not support to be generated with a parallel build. So we compile & install in a first
   stage in ``-j4`` (or whatever) then we generate the documentation in ``-j1``

Under |RHEL6| or clones, you must build using the |devtoolset|, the version is to
be given as argument:

.. code-block:: sh

   dummy@lepka:coriolis> ./bootstrap/ccb.py --project=coriolis \
                                            --devtoolset=8 --make="-j4 install"

If you want to use Qt 5 instead of Qt 4, modify the previous steps as follows:

* At **step 1**, do not install the |QT| 4 related development package (``qt4-devel``),
  but instead:

  .. code-block:: sh

     dummy@lepka:~> yum install -y qt5-qtbase-devel qt5-qtsvg-devel              # Qt 5.
   
  The package ``qwt-qt5-devel`` and it's dependency ``qwt-qt5`` are not provided
  by any standard repository (like |EPEL|). You may download them from the
  `LIP6 Addons Repository <https://ftp.lip6.fr/pub/linux/distributions/slsoc/soc/7/addons/x86_64/repoview/letter_q.group.html>`_
  Then run:

  .. code-block:: sh
   
     dummy@lepka:~> yum localinstall -y qwt-qt5-6.1.2-4.fc23.x86_64.rpm        \
                                        qwt-qt5-devel-6.1.2-4.fc23.x86_64.rpm  # Qwt for Qt 5.

* At **step 4**, add a ``--qt5`` argument to the ``ccb.py`` command line.

* The |Python| scripts that make use of |PyQt| in ``crlcore`` and ``cumulus`` must be
  edited to import ``PyQt5`` instead of ``PtQt4`` (should find a way to automatically
  switch between the two of them).

The complete list of |ccb| functionalities can be accessed with the ``--help`` argument.
It also may be run in graphical mode (``--gui``).


Building a Debug Enabled Version
--------------------------------

The ``Release.Shared`` default version of the |Coriolis| is built stripped of symbols
and optimized so that it makes analysing a core dump after a crash difficult. In the
(unlikely) case of a crash, you may want to build, alongside the optimized version,
a debug one which allows forensic examination by |gdb| (or |valgrind| or whatever).

Run again ``ccb.py``, adding the ``--debug`` argument:

.. code-block:: sh

   dummy@lepka:coriolis> ./bootstrap/ccb.py --project=support  \
                                            --project=coriolis \
                                            --make="-j4 install" --debug


As |cgt| is a |Python| script, the right command to run |gdb| is:

.. code-block:: sh

   dummy@lepka:work> gdb python core.XXXX 


.. Building the Devel Branch
.. -------------------------
.. 
.. In the |Coriolis| |git| repository, two branches are present:
.. 
.. * The :cb:`master` branch, which contains the latest stable version. This is the 
..   one used by default if you follow the above instructions.
.. 
.. * The :cb:`devel` branch, which obviously contains the latest commits from the
..   development team. To use it instead of the :cb:`master` one, do the following
..   command just after the first step: ::
.. 
..       dummy@lepka:coriolis> git checkout devel
..       dummy@lepka:coriolis> ./bootstrap/ccb.py --project=coriolis \
..                                                --make="-j4 install" --debug
.. 
..   Be aware that it may require newer versions of the dependencies and may introduce
..   incompatibilities with the stable version.

|newpage|


Installing on |Debian| 9, |Ubuntu| 18 or compatible distributions
-----------------------------------------------------------------

First, install or check that the required prerequisites are installed:

.. code-block:: sh

   dummy@lepka:~> sudo apt-get install -y build-essential binutils-dev                     \
                                          git cmake bison flex gcc python-dev              \
                                          libboost-all-dev libboost-python-dev             \
                                          zlib1g-dev libxml2-dev rapidjson-dev libbz2-dev

To use with Qt 4:

.. code-block:: sh

   dummy@lepka:~> sudo apt-get install -y qt4-dev-tools libqwt-dev python-qt4

To use with Qt 5:

.. code-block:: sh

   dummy@lepka:~> sudo apt-get install -y qtbase5-dev libqt5svg5-dev libqwt-qt5-dev \
                                          python-pyqt5

.. note:: **Do not install both versions of Qwt** (for Qt 4 and Qt 5),
          this will confuse the installer and end up with a non functional software
          (it uses the headers from one Qt and libraries from the other version).

Second step is to create the source directory and pull the |git| repository:

.. code-block:: sh

   dummy@lepka:~> mkdir -p ~/coriolis-2.x/src
   dummy@lepka:src> cd ~/coriolis-2.x/src
   dummy@lepka:src> git clone https://github.com/lip6/coriolis.git

Third and final step, build & install:

.. code-block:: sh

   dummy@lepka:src> cd coriolis
   dummy@lepka:coriolis> git checkout devel
   dummy@lepka:coriolis> ./bootstrap/ccb.py --project=coriolis \
                                            --make="-j4 install"


Additionnal Requirement under |MacOS|
-------------------------------------

|Coriolis| makes use of the :cb:`boost::python` module, but the |macports| |boost|
seems unable to work with the |Python| bundled with |MacOS|. So you have to install
both of them from |macports|:

.. code-block:: sh

   dummy@macos:~> port install boost +python27
   dummy@macos:~> port select python python27
   dummy@macos:-> export DYLD_FRAMEWORK_PATH=/opt/local/Library/Frameworks

The last two lines tell |MacOS| to use the |Python| from |macports| and *not* from
the system.

Then proceed with the generic install instructions.


|Coriolis| & Docker
~~~~~~~~~~~~~~~~~~~

Under ``bootstrap/docker/`` scripts and configuration files are provided that
allow to rebuild |Alliance| and |Coriolis| and perform the regression tests
of ``alliance-check-toolkit``. You may have a look at the ``Dockerfile.system``
configuration file to see exactly how to setup a vanilla system to build
|Coriolis|.

To run the docker tests, call the ``dockerManage.sh`` scripts with the relevant
arguments:

.. code-block:: sh

   ego@home:debian-9> ../../dockerManage.sh -bS  # build both system & coriolis images.
   ego@home:debian-9> ../../dockerManage.sh -r   # compile & check coriolis.
   ego@home:debian-9> ../../dockerManage.sh -C   # clear the images.



Packaging Coriolis
~~~~~~~~~~~~~~~~~~

Packager should not use |ccb|, instead ``bootstrap/Makefile.package`` is provided
to emulate a top-level ``autotool`` makefile. Just copy it in the root of the
|Coriolis| git repository (``~/corriolis-2.x/src/coriolis/``) and build.

Sligthly outdated packaging configuration files can also be found under ``bootstrap/``:

* ``bootstrap/coriolis2.spec.in`` for |rpm| based distributions.
* ``bootstrap/debian`` for |Debian| based distributions.


Hooking up into |Alliance|
~~~~~~~~~~~~~~~~~~~~~~~~~~

|Coriolis| relies on |Alliance| for the cell libraries. So after installing or
packaging, you must configure it so that it can found those libraries.

The easiest way is to setup the |Alliance| environment (i.e. sourcing
``.../etc/profile.d/alc_env.{sh,csh}``) **before** setting up |Coriolis| environment
(see the next section). To understand how |Coriolis| find/setup |Alliance| you may
have look to the `Alliance Helper`.


Setting up the Environment (coriolisEnv.py)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To simplify the tedious task of configuring your environment, a helper is provided
in the ``bootstrap`` source directory (also installed in the directory
``.../install/etc/coriolis2/``) :

.. code-block:: sh

   ~/coriolis-2.x/src/coriolis/bootstrap/coriolisEnv.py

Use it like this:

.. code-block:: sh

   dummy@lepka:~> eval `~/coriolis-2.x/src/coriolis/bootstrap/coriolisEnv.py`

.. note:: **Do not call that script in your environement initialisation.**
   When used under |RHEL6| or clones, it needs to be run in the |devtoolset|
   environement. The script then launch a new shell, which may cause an
   infinite loop if it's called again in, say :cb:`~/.bashrc`.

   Instead you may want to create an alias:

   .. code-block:: sh

      alias c2r='eval "`~/coriolis-2.x/src/coriolis/bootstrap/coriolisEnv.py`"'
