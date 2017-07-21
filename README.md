# MultiScreenStopwatch
Display a stopwatch fullscreen on one screen while controlling it from another.

This application, written in C++ for OSX, started as a comparison of QT vs wxWidgets. I chose wxWidgets, and moved forward. It handles displaying a count up timer (stopwatch) on one screen, while a dialog on another controls it.

There is still plenty to do, but the basics are here.

TODO:

Save defaults to a config file (plist?)

Separate what is often adjusted from what is rarely adjusted. Move rarely adjusted items to a separate dialog. The main dialog should probably have the control buttons and the "Timer Minutes" and "Time left before waring" fields only.

Internationalization - Perhaps wxWidgets can help here too. http://docs.wxwidgets.org/trunk/overview_i18n.html
