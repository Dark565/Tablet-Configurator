<h1>EWL-Based X11 tablet configuration program</h1>

<b>Installation:</b>
<br>If you want to install this program, compile it using: `make`.
You can pass additional argument `EWL_TYPE=LINKED` for make, to compile program using default dynamic liblaries' link method.

After this step, write `make install` with root permissions to install it into `/usr/bin/` directory.


<b>Usage:</b>
<br>`tablet x0%-x1% y0%-y1% monitor_index`

Where x and y is width and height.
After line, you pass second coordinate parameter, to set range.

Example usage:
`tablet 25%-75% 25%-75% 0`

Command above will set your tablet register area to middle of it.
