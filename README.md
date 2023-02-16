# Robson
Robson is a simple Linux Kernel Module (LKM) rootkit that uses the kernel's kprobes tracing feature as a hooking mechanism. This rootkit utilizes performance tracing mechanisms that allows it to gain privileged access to the kernel and its functions without using other common methods.

This can be developed further with more features, extending the rootkit should be easy enough by following the same example used for filldir64 in the code for other functions.

# Disclaimer
It is important to note that this is a proof-of-concept rootkit and should not be used in a production environment. As such, the author of this software cannot be held responsible for any damage incurred through the use of this rootkit. This rootkit is mainly intended for educational and research purposes, and should be treated as such.

# Usage
To compile the rootkit, simply run `make`. To load the rootkit, run `insmod robson.ko`.

# References
- Kernel Probes: https://www.kernel.org/doc/Documentation/kprobes.txt
- Kernel instrumentation using kprobes: http://phrack.org/issues/67/6.html
