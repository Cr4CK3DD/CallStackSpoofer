# Suppressor
## Stack spoofing
- Stack spoofing is a really cool malware technique that isn’t new, but has been receiving some more attention recently.
- The method i used simply involves pushing `ret` gadget from loaded DLL and return address to our function (Suppressor).

## why using stack spoofing technique?
- EDRs utilize the call stack of a function call to determine whether a function is malicious or not, by verifying  that the caller’s return address resolves to a loaded module.

- Indirect syscall without stack spoofing technique:

![stack not spoofed](https://github.com/Cr4CK3DD/Suppressor/assets/93877982/eae7fae4-e50f-40db-908d-45009324c1e5)


- Indirect syscall with stack spoofing technique:

![Spoofed stack](https://github.com/Cr4CK3DD/Suppressor/assets/93877982/c3fe93d4-3fd9-40e6-b84a-364dc7fe2fde)


## Resources & References:
- [x64 return address spoofing source explanation.](https://www.unknowncheats.me/forum/anti-cheat-bypass/268039-x64-return-address-spoofing-source-explanation.html)
- [reflective call stack detections evasions.](https://securityintelligence.com/x-force/reflective-call-stack-detections-evasions/)
- [DEF CON 30 - Kyle Avery](https://www.youtube.com/watch?v=edIMUcxCueA&t=1864s)
- [Adding x86, x64 Assembly Language code to the Visual Studio C++ project.](https://dennisbabkin.com/blog/?t=cpp-and-assembly-coding-in-x86-x64-assembly-language-in-visual-studio)
- [BokuLoader.](https://github.com/boku7/BokuLoader)
- [AceLdr.](https://github.com/kyleavery/AceLdr)
