# ASCII Matrix

My attempt at recreating the iconic Matrix "digital rain" effect in C.  
This repo contains two versions: a simple one that just prints stuff, and a more advanced one that actually simulates falling characters.

## What is this?

You know that iconic green text falling down the screen in The Matrix? Yeah, I wanted to make that.  
Started simple, then got a bit carried away and made a proper simulation with physics and everything.

## The Two Versions

### Version 1: The "I'm just learning" approach

This was my first shot at it. Characters appear with random spacing, kind of flowing down the terminal. It's simple, it works, but it's not really... Matrix-y.

What it does:
- Prints random letters with random spacing
- Random delays between characters (0-20ms)
- New line every 10 characters
- That's pretty much it

What it doesn't do:
- Actually simulate falling characters
- Hide the cursor (so it's visible the whole time)
- Adapt to your terminal size
- Look particularly impressive

Honestly, it's more like a stream of random text than the actual Matrix effect. But hey, we all start somewhere.

### Version 2: The "okay now I know what I'm doing" approach

After learning more about terminal control and ANSI codes, I rewrote the whole thing from scratch. This version actually simulates individual drops falling down the screen.

What it does:
- Detects your terminal size automatically
- Creates individual "drops" with their own position and speed
- Hides the cursor for a cleaner look
- Only updates the parts of the screen that change (much more efficient)
- Each drop falls at its own speed (1-2 units per frame)
- Handles Ctrl+C gracefully (cursor gets restored properly)
- Uses ANSI escape codes to control the terminal

Technical stuff:
- Each drop is a struct with x, y, character, and speed
- Creates as many drops as your terminal is wide
- Efficiently erases and redraws only what's needed
- Recycles drops when they fall off the bottom

## Requirements

- A C compiler (gcc, clang, whatever you have)
- Unix-like system (Linux, macOS)
- Terminal with ANSI escape code support (basically any modern terminal)

## How to compile

```bash
# Version 1
gcc ascii_matrix_v1.c -o matrix_v1

# Version 2
gcc ascii_matrix_v2.c -o matrix_v2
```

If you want it faster:
```bash
gcc -O2 ascii_matrix_v2.c -o matrix_v2
```

## How to run

### Version 1
```bash
./matrix_v1
```
It'll start printing immediately. Press `Ctrl+C` to stop.

### Version 2
```bash
./matrix_v2
```
Shows your terminal dimensions for a moment, then starts the animation.  
Press `Ctrl+C` to exit cleanly.

Pro tips for version 2:
- Run it fullscreen for the best effect
- Set your terminal text color to green if you want the authentic Matrix vibe
- Dark background helps with the contrast


## Technical notes

### Version 1
Simple infinite loop printing random characters. Spacing is handled with pre-allocated string arrays. Timing uses `usleep()`. No cursor control whatsoever.

### Version 2
Each drop is its own little object with position, character, and speed. Uses `ioctl()` to get terminal dimensions. ANSI escape sequences for everything:
- `\033[?25l` - hide cursor
- `\033[?25h` - show cursor
- `\033[2J` - clear screen
- `\033[H` - move cursor to top
- `\033[y;xH` - move cursor to specific position

Signal handler for `SIGINT` makes sure the cursor gets restored when you exit.

## What I learned

This project shows the difference between "making it work" and "making it work well."  
Version 1 gets the job done in the simplest way possible.  
Version 2 taught me about proper resource management, I/O optimization, data structures for simulations, and system responsiveness.

## Future ideas

- Add ANSI colors (bright/dark green for the authentic look)
- Longer trails with color fading
- Command line options for speed and density
- Windows support (would need different terminal APIs)
- Interactive mode with keyboard controls

## License

Open source, do whatever you want with it.

## Author

Made by a computer science student who thought "hey, that Matrix effect looks cool, I wonder how hard it is to make."  
Turns out: not that hard for a basic version, pretty interesting for a good one.