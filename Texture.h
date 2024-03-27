#pragma once
class Texture
{
	public:
	Texture(const char* path);
	~Texture();
	void loadTexture(const char* path);
	void bindTexture();
	void unbindTexture();
	private:
		//Renderer ID
		unsigned int m_RendererID;
		//what is m_BPP?
		//Bits per pixel	
		int m_Width, m_Height, m_BPP;
};

