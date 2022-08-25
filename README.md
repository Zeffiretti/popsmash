# PopSmash: Find the bubbles you want to smash

<center><img src='doc/demo.gif' align='center' style=' width:300px;height:100 px;BORDER:#007979 5px solid'/></center>

## Build

The program has been tested with cmake on Ubuntu 20.04 and Windows 10/11 platform. The visual studio 2022 project has also been tested on Windows 10/11 platform.

### CMake

- On Ubuntu 20.04:

```bash
$ git clone https://github.com/Zeffiretti/popsmash.git
$ cd popsmash
$ ./scripts/build_linux.sh
```

- On Windows 10/11, you can run `scripts/build_win.bat`, or run cmake manually.

### Visual Studio

The VS project is provided under the `projects` directory. Open `popsmash.sln` and confirm `mihoyo` project has been set as the startup project.