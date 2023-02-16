# Robson
Robson is a simple LKM rootkit that uses the Linux kernel's kprobes tracing feature as a hooking mechanism.

# Disclaimer
This is a proof-of-concept rootkit and should not be used in a production environment. It is not intended to be used maliciously, and the author is not responsible for any damage caused by the use of this software.

# Usage
To compile the rootkit, simply run `make`. To load the rootkit, run `insmod robson.ko`.

# References
- Kernel Probes: https://www.kernel.org/doc/Documentation/kprobes.txt
- Kernel instrumentation using kprobes: http://phrack.org/issues/67/6.html