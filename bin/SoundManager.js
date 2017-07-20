function _SoundManagerAdd(name, fileName)
{
    Module.SoundManagerAdd(Pointer_stringify(name), Pointer_stringify(fileName));
}

function _SoundManagerPlay(name)
{
    Module.SoundManagerPlay(Pointer_stringify(name));
}

function _SoundManagerPause(name)
{
    Module.SoundManagerPause(Pointer_stringify(name));
}

function _SoundManagerStop(name)
{
    Module.SoundManagerStop(Pointer_stringify(name));
}

function _SoundManagerLoop(name)
{
    Module.SoundManagerLoop(Pointer_stringify(name));
}

function _SoundManagerSetVolume(name, volume)
{
    Module.SoundManagerSetVolume(Pointer_stringify(name), volume);
}