# recycle-bin

> Move files and folders to the Windows recycle bin


## Install

[Download](https://github.com/sindresorhus/recycle-bin/releases/latest) the binary and put it somewhere in your [`%path%`](http://stackoverflow.com/a/28778358/64949).

...And see notes below  
## Usage

```

Usage: recycle-bin <path> [...]
```


## Build
you should have msvc  

- first : run `c.ps1` script from `\release`  
in case of troubles run `Set-ExecutionPolicy -ExecutionPolicy Unrestricted` first.  
to run a script use  
`cd ` (drag `release` dir there)  
`.\c`  
windows powershell, admin priv's
 - second : build both solutions .  
 use `Win32 - Release` Conf or copy script to others folders and run there.
  
  
  build done  
  
  
  
Anywhere use of binaries possible only after run of `c.ps1` . It should be located in same place with `.dll` 

## Related

- [empty-recycle-bin](https://github.com/sindresorhus/empty-trash) - Empty the Windows recycle bin
- [trash](https://github.com/sindresorhus/trash) - Move files and folders to the trash - cross-platform
- [empty-trash](https://github.com/sindresorhus/empty-trash) - Empty the trash - cross-platform


## License

MIT © [Sindre Sorhus](http://sindresorhus.com)
