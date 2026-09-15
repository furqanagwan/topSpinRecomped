# Research notes

## Title info
- Title: Top Spin 3 (USA, Europe), English, French, German, Spanish, Italian
- Title ID: 545407FF, media ID 28AA9C46, executable version 0.0.0.1 (built 2008-04-28)
- Achievements: 41, 1000 Gamerscore
- Guest DLL modules: none
- Disc: 96 files, 4,264,538,917 bytes; `default.xex` is 4,587,520 bytes
- Data: `.arc` archives per venue and mode, Bink video (`.bik`), FMOD sound banks (`.fsb`)

## Codegen

### 2026-09-15: first pass and discovery
The first time through the framework's full new-game workflow in one go.
`stabilize_codegen.py` seeded one unresolved call target and codegen was clean;
passes take about 15 seconds. One function (0x82278948) is 1.5 MB, over
`max_file_size_bytes`; it compiles. The first build linked with no missing
kernel imports.

With the image dumped: 58 functions referenced from data, 1,054 from code gaps
and one whose address is only built in code. Stabilizing took ten rounds of
disabling seeds that split functions, including 7 found only from leftover
unresolved-branch stubs in the generated code; `prune_bad_seeds.py --image`
disabled 3 more. No under-counted jump tables. Result: 520 seeds, 597
disabled, no unresolved stubs, clean build.

## Runtime

### 2026-09-15: first launch
Boots with no errors or crash: a white splash, the Bink intro video, then the
front end with a real-time 3D player portrait by 90 seconds. The only
warnings in a 3,177-line debug log are the missing `gamecontrollerdb.txt`, the
harmless `ShaderDumpxe:` probe and `d:\ActivateDebugMode.txt`, a debug-mode
switch file the game looks for. Not yet tested: controller input, a match,
career.

### 2026-09-15: repeating intro audio
Repeating audio was heard during the intro video on the first launch, which ran
with `--log_level=debug`. To find out whether the game or the host repeated it,
the function that calls `XAudioSubmitRenderDriverFrame` (sub_82173038) was
wrapped to hash and record every submitted frame for 74 seconds: no frame
repeated one from the previous 1.4 seconds, no passage of half a second or more
repeated at any lag up to 12 seconds, and steady-state submission was 187.75
frames a second against the 187.5 the output consumes. Later runs at the
default log level played the intro correctly. Debug logging on the audio and
kernel paths is the likely cause: it slows the threads that feed the mixer.
If it comes back, the samples pointer sits in the stack slot at 88(r1) of
sub_82173038.
