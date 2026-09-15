# Research notes

## Title info
- Title: Top Spin 4 (USA, Europe), English, French, German, Spanish, Italian
- Title ID: 54540859, media ID 60819732, executable version 0.0.0.3 (built 2011-01-12)
- Achievements: 40, 1000 Gamerscore
- Disc: 230 files, 5,737,767,977 bytes
- Code: `default.xex` (638,976 bytes) is a small loader; the game is in two DLL
  modules loaded from the game root, `Loader_DLL.xex` (2,580,480 bytes) and
  `Swing_DLL.xex` (5,083,136 bytes)
- Data: `.arc` archives, WMV video (`Media\XUI\*.wmv`), XUI packages
  (`Media\XUI\*.xzp`), FMOD (`.fsb`) and XACT (`.xwb`) sound banks

## Codegen

### 2026-09-15: DLL modules
The first game with guest DLL modules. `rexglue init --scan-dll` only looks for
`.dll` files, so the modules were added to the manifest by hand; running the
loader alone showed the guest paths (`Loader_DLL.xex`, `Swing_DLL.xex` at the game
root). The framework's analysis scripts gained module support for this game:
per-module `config/<module>/functions.toml`, module-aware `stabilize_codegen.py`,
`--module` on the scan scripts, and `RECOMP_DUMP_MODULE` for dumping a DLL once
the game loads it.

Loader_DLL needed 3 unresolved call targets and Swing_DLL 4. Loader_DLL's
0x8317F628 is a leaf with early returns whose last block branches back to
0x8317F634; explicit bounds `end = 0x8317F66C` fixed it.

### 2026-09-15: discovery
Loader_DLL was dumped once it loaded: 111 functions referenced from data, 225
from code gaps and 2 whose address is built in code; stabilizing disabled 16.
The main executable added 13 seeds. Swing_DLL has not been dumped yet because
the game crashes before loading it. Codegen is clean in all three modules with
no unresolved stubs.

## Runtime

### 2026-09-15: thread start after a no-return call
`Call to invalid or unregistered function at 0x833F9780`: a thread routine in
Loader_DLL that sits right after a function ending in `ExTerminateThread`, so
codegen never started a function there. Seeded directly.

### 2026-09-15: null read after the intro video (open)
Plays the 2K intro (WMV, the O2 arena) with sound, then dies about 12 seconds
after Loader_DLL registers: `Unhandled guest access violation: read of guest
0x000001A4` on the main thread. A RelWithDebInfo build symbolizes it to
`sub_83442C20` at `lwz r11,420(r31)` (loc_83442C74). The same read succeeds at
the top of the loop, so r31, a callee-saved register, comes back as 0 from
`sub_83442B40` or `sub_834429C0`. Both save and restore r26-r31 correctly
through `__savegprlr_26`/`__restgprlr_26` (checked against the dump), so the
saved slot is probably overwritten during one of their indirect `bctrl` calls.

Just before the crash the game probes for its XUI packages in
`Locale\eng\Media\XUI\SKU\WW_EFIGS\eng\`, `Locale\eng\Media\XUI\eng\` and
`Media\XUI\eng\`; the packages exist only in `Media\XUI\`. Whether it then opens
those successfully (successful opens aren't logged) and whether the UI load is
related to the crash is not yet known. Next step: trace the indirect calls in
the two callees and watch writes to r31's save slot.
