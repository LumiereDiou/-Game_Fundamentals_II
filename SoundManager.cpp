#include "SoundManager.h"
#include <iostream>

std::map<std::string, Mix_Chunk*> SoundManager::s_sfxs;
std::map<std::string, Mix_Music*> SoundManager::s_music;

bool SoundManager::Init()
{
	int errorCode = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

	if (errorCode == 0)
	{
		std::cout << "Mix_OpenAudio() success" << std::endl;
	}
	else
	{
		std::cout << "Mix_OpenAudio() failed. Error -" << Mix_GetError() << std::endl;
		system("pause");
		return false;
	}

	int audioFlags = MIX_INIT_MP3;
	errorCode = Mix_Init(audioFlags);
	if (errorCode != audioFlags)
	{
		std::cout << "Mix_OpenAudio() failed. Error -" << Mix_GetError() << std::endl;
		system("pause");
		return false;
	}
	return true;
}

bool SoundManager::LoadMusic(const std::string& file_name, const std::string& id)
{
	Mix_Music* pMusic = Mix_LoadMUS(file_name.c_str());
	if (pMusic == nullptr)
	{
		std::cout << "Load music failed. Error -" << Mix_GetError() << std::endl;
		return false;
	}
	s_music[id] = pMusic;
	return true;
}

void SoundManager::UnloadMusic(const std::string& id)
{
	if (s_music.find(id) != s_music.end())
	{
		Mix_FreeMusic(s_music[id]);
		s_music.erase(id);	
	}
	else
	{
		std::cout << "Unload music failed. " << id << " id not found" << std::endl;
	}
}

void SoundManager::PlayMusic(const std::string& id, int loop, int fade_in)
{
	if (Mix_FadeInMusic(s_music[id], loop, fade_in) == -1)
		std::cout << "Unable to play music. " << Mix_GetError() << std::endl;
}

void SoundManager::StopMusic(const int fade_out)
{
	if (Mix_PlayingMusic())
		Mix_FadeOutMusic(fade_out);
}

void SoundManager::PauseMusic()
{
	if (Mix_PlayingMusic())
		Mix_PauseMusic();
}

void SoundManager::ResumeMusic()
{
	if (Mix_PausedMusic())
		Mix_ResumeMusic();
}

void SoundManager::SetMusicVolume(const int vol)
{
	if (vol >= 0 && vol <= MIX_MAX_VOLUME)
		Mix_VolumeMusic(vol);
}

bool SoundManager::LoadSound(const std::string& file_name, const std::string& id)
{
	Mix_Chunk* pChunk = Mix_LoadWAV(file_name.c_str());
	if (pChunk == nullptr)
	{
		std::cout << "Load sfx failed. Error -" << Mix_GetError() << std::endl;
		return false;
	}
	s_sfxs[id] = pChunk;
	return true;
}

void SoundManager::UnloadSound(const std::string& id)
{
	if (s_sfxs.find(id) != s_sfxs.end())
	{
		Mix_FreeChunk(s_sfxs[id]);
		s_sfxs.erase(id);
	}
	else
	{
		std::cout << "Unload sfx failed. " << id << " id not found" << std::endl;
	}
}

void SoundManager::PlaySound(const std::string& id, int loop, int channel)
{
	if (channel != -1 && Mix_Playing(channel))
		return;
	if (Mix_PlayChannel(channel, s_sfxs[id], loop) == -1)
		std::cout << "Unable to play sfx. " << Mix_GetError() << std::endl;
}

void SoundManager::StopSound(int channel)
{
	Mix_HaltChannel(channel);
}

void SoundManager::SetSoundVolume(const int vol, int channel)
{
	if (vol >= 0 && vol <= MIX_MAX_VOLUME)
		Mix_Volume(channel, vol);
}

void SoundManager::SetAllVolume(const int vol)
{
	SetMusicVolume(vol);
	SetSoundVolume(vol);
}

void SoundManager::Quit()
{
	if (Mix_Playing(-1))
		Mix_HaltChannel(-1);

	for (auto const& i : s_sfxs)
		Mix_FreeChunk(s_sfxs[i.first]);
	s_sfxs.clear();

	if (Mix_PlayingMusic())
		Mix_HaltMusic();

	for (auto const& i : s_music)
		Mix_FreeMusic(s_music[i.first]);
	s_music.clear();

	Mix_CloseAudio();
	Mix_Quit();
}