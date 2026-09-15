<p align="center">
  <img src="docs/icon.png" alt="Top Spin 4" width="320">
</p>

<h1 align="center">Top Spin 4</h1>

<p align="center">
  Native PC static recompilation of the Xbox 360 version, built on the
  <a href="../README.md">topSpinRecomped</a> framework and ReXGlue.
</p>

## Game

| | |
| --- | --- |
| Developer | PAM Development |
| Publisher | 2K Sports |
| Series | Top Spin |
| Platform recompiled | Xbox 360 |
| Released | March 2011 |
| Genre | Sports, tennis |
| Achievements | 40, 1000 Gamerscore |

## Regions

| Region | Serial | Status |
| --- | --- | --- |
| 🇺🇸 🇪🇺 USA, Europe | `TT-2137` | 🟨 In progress (the disc below) |

Only the tested disc's `default.xex` has been recompiled. Other regional
executables are likely to differ and may need their own codegen pass.
Region list from [Redump](http://redump.org/discs/system/xbox360/).

## Disc

| | |
| --- | --- |
| Region | 🇺🇸 🇪🇺 USA, Europe |
| Title ID | `54540859` |
| Media ID | `60819732` |
| Executable version | 0.0.0.3 (built 2011-01-12) |
| Languages | English, French, German, Spanish, Italian |
| Contents | 230 files, 5,737,767,977 bytes |
| Executable | `default.xex`, 638,976 bytes (a loader) |
| DLL modules | `Loader_DLL.xex` (2,580,480 bytes), `Swing_DLL.xex` (5,083,136 bytes) |
| Video format | WMV (`.wmv`) |

## Status

| Area | State |
| --- | --- |
| Boot, intro video | Plays the 2K intro with sound |
| Front end | Not reached: a guest null-pointer read about 12 seconds after Loader_DLL loads (see [docs/NOTES.md](docs/NOTES.md)) |
| Codegen | Clean in all three modules |
| Controller input, matches, career | Not yet tested |
| Xbox PC app, UWP builds | Configured, not yet tested |

No release until it reaches the front end.

## Play

1. Download `TopSpin4-v<version>-windows-x64.zip` from
   [Releases](https://github.com/furqanagwan/topSpinRecomped/releases?q=topspin4)
   and extract it to a folder you can write to.
2. Run `Top Spin 4.exe` and choose your Xbox 360 ISO (USA/Europe disc, see
   [Regions](#regions)); the files are copied once.
3. Open the system menu with **View + Menu** (or **Esc**) for Settings and Exit.

## System requirements

| | Required |
| --- | --- |
| OS | Windows 10 version 2004 (build 19041) or Windows 11, 64-bit |
| Processor | 64-bit x86 CPU with SSE4.1 |
| Graphics | DirectX 12 GPU (feature level 11_0) |
| Memory | 8 GB RAM recommended |
| Storage | 6 GB, plus room for the ISO while it is copied |
| Software | [Microsoft Visual C++ Redistributable 2015-2022 (x64)](https://aka.ms/vs/17/release/vc_redist.x64.exe) |
| Game | Your own Top Spin 4 (USA, Europe) Xbox 360 disc image |

Tested on an Intel Core Ultra 9 275HX, GeForce RTX 5080 Laptop GPU and 32 GB RAM
(Windows 11).

## Build from source

```
rexglue extract "<your disc>.iso" topspin4\assets
.\framework\scripts\build.ps1 -Game topspin4
```

Setup is described in [CONTRIBUTING.md](../CONTRIBUTING.md).

## Default settings

`settings/top_spin_4.toml` starts from the NBA LIVE settings (`rov` / `fsi`
render target paths, no background pipeline creation, 60 Hz vsync). Whether
Top Spin 4 needs each of them has not been tested separately.

## Recompilation notes

| | |
| --- | --- |
| Modules | `default` (the loader, seeds in `config/functions.toml`), `Loader_DLL` and `Swing_DLL` (seeds in `config/<module>/functions.toml`) |
| Function seeds | default 13, Loader_DLL 326, Swing_DLL 4 |
| Disabled seeds | Loader_DLL 16 |
| Jump tables | No under-counted tables in the dumped modules |
| Kernel stubs | None needed beyond the framework's |

Swing_DLL hasn't been through function discovery yet: the game crashes before
loading it. The full log is in [docs/NOTES.md](docs/NOTES.md).

## Xbox Developer Mode (UWP)

```powershell
.\framework\scripts\build.ps1 -Game topspin4 -Preset win-amd64-uwp-release
.\framework\scripts\package_uwp.ps1 -Game topspin4 -Register
.\framework\scripts\package_uwp.ps1 -Game topspin4 -Pack
```

## Artwork

`docs/icon.png` is the title image from `default.xex`, upscaled to 1024x1024.
To regenerate the exe icon and Xbox app images locally:

1. `rexglue init --project-name top_spin_4 --xex-path assets\default.xex achievements assets\default.xex metadata`
2. Upscale `metadata/icons/title.png` 4x twice with Real-ESRGAN
   (`realesrgan-x4plus`) to `metadata/gdk_hd/title_1024.png`, or copy
   `docs/icon.png` there.
3. `.\framework\scripts\generate_artwork.ps1 -Game topspin4 -ProjectName top_spin_4`

## Legal

Not affiliated with or endorsed by 2K, Take-Two Interactive or Microsoft. Top Spin
and 2K Sports are trademarks of Take-Two Interactive. You must own the game.
