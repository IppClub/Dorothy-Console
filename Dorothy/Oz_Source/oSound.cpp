#include "oSound.h"
using namespace Dorothy;

oSound::oSound():
m_lpkSound(NULL){}

oSound::~oSound()
{
	oSound::Release();
}

bool oSound::LoadFromFile( const char* filename )
{
	fstream kWave;
	/*�򿪲����ļ�*/
	kWave.open(filename,ios::in|ios::binary);
	if (kWave.is_open())
	{
		oInt8 aiID[5];
		/*��ȡ�ļ���ʶ��"RIFF"*/
		kWave.read(aiID,sizeof(oInt8)*4);
		aiID[4] = '\0';
		/*�����ʶ������"RIFF"�����˳������ش������*/
		if (0 != strcmp(aiID,"RIFF"))
		{
			return false;
		}
		oUInt32 iSize;
		/*��ȡ�������ݴ�С*/
		kWave.read((oInt8*)&iSize,sizeof(oUInt32));
		/*��ȡ���ͱ�ʶ��"WAVE"*/
		kWave.read(aiID,sizeof(oInt8)*4);
		aiID[4] = '\0';
		/*������ͱ�ʶ������"WAVE",���˳������ش������*/
		if (0 != strcmp(aiID,"WAVE"))
		{
			return false;
		}
		/*����"FMT"�ַ���*/
		kWave.seekg(4,ios::cur);
		/*��ȡ��ʽ�쳤��*/
		oUInt32 iFormatLength;
		kWave.read((oInt8*)&iFormatLength,sizeof(oUInt32));
		/*��ȡWAVEFORMATEX�ṹ��*/
		WAVEFORMATEX kWaveFormat;
		kWave.read((oInt8*)&kWaveFormat,sizeof(WAVEFORMATEX));
		/*ǰ������WAVEFORMATEX��cbSize����������ֽڣ����ں��������ֽ�*/
		kWave.seekg(2,ios::cur);
		kWaveFormat.cbSize = 0;
		/*��ȡ�������ݴ�С*/
		oUInt32 iDataSize;
		kWave.read((oInt8*)&iDataSize,sizeof(oUInt32));
		/*��ȡ��������*/
		oUInt8 *pkSoundBuffer = new oUInt8[iDataSize];
		kWave.read((oInt8*)pkSoundBuffer,sizeof(oUInt8)*iDataSize);
		/*���DirectSound������������Ϣ*/
		DSBUFFERDESC kBufferDesc;
		ZeroMemory(&kBufferDesc,sizeof(DSBUFFERDESC));
		kBufferDesc.dwSize = sizeof(DSBUFFERDESC);
		kBufferDesc.dwBufferBytes = iDataSize;
		kBufferDesc.lpwfxFormat = &kWaveFormat;
		kBufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
		/*��������������*/
		if (FAILED(((LPDIRECTSOUND8)(oSoundPlayer::GetInstance()->GetDevice()))->CreateSoundBuffer(&kBufferDesc,
			(LPDIRECTSOUNDBUFFER*)(&m_lpkSound),NULL)))
		{
			return false;
		}
		/*����������*/
		LPVOID lpvAudio;
		DWORD dwBytes;
		if (FAILED(((LPDIRECTSOUNDBUFFER)m_lpkSound)->Lock(0,0,&lpvAudio,&dwBytes,NULL,NULL,DSBLOCK_ENTIREBUFFER)))
		{
			return false;
		}
		/*���������ݿ�����DirextSound������*/
		memcpy(lpvAudio,pkSoundBuffer,dwBytes);
		((LPDIRECTSOUNDBUFFER)m_lpkSound)->Unlock(lpvAudio,dwBytes,NULL,0);
		/*ɾ�����沨�����ݵ��ڴ棬Ȼ��ر��ļ�*/
		delete [] pkSoundBuffer;
		kWave.close();
	}
	return true;
}

void oSound::SetVolume( oUInt32 iVolume )
{
	((LPDIRECTSOUNDBUFFER)m_lpkSound)->SetVolume(iVolume == 0 ? -10000 : -30*(100-iVolume));
}

void oSound::Play( bool bLoop )
{
	/*����ʼλ����Ϊ����λ��*/
	((LPDIRECTSOUNDBUFFER)m_lpkSound)->SetCurrentPosition(0);
	/*��������*/
	((LPDIRECTSOUNDBUFFER)m_lpkSound)->Play(0,NULL,(bLoop ? DSBPLAY_LOOPING : 0));
}

void oSound::Stop()
{
	((LPDIRECTSOUNDBUFFER)m_lpkSound)->Stop();
}

void oSound::Release()
{
	if (NULL != m_lpkSound)
	{
		((LPDIRECTSOUNDBUFFER)m_lpkSound)->Release();
		m_lpkSound = NULL;
	}
}