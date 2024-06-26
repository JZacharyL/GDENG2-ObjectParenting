#include "CreditsScreen.h"
#include "UIManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Stb/stb_image.h"

bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
    // Load from disk into a raw RGBA buffer
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    // Create texture
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = image_width;
    desc.Height = image_height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;

    ID3D11Texture2D* pTexture = NULL;
    D3D11_SUBRESOURCE_DATA subResource;
    subResource.pSysMem = image_data;
    subResource.SysMemPitch = desc.Width * 4;
    subResource.SysMemSlicePitch = 0;
	GraphicsEngine::get()->getDirectXDevice()->CreateTexture2D(&desc, &subResource, &pTexture);

    // Create texture view
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = desc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;
    GraphicsEngine::get()->getDirectXDevice()->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
    pTexture->Release();

    *out_width = image_width;
    *out_height = image_height;
    stbi_image_free(image_data);

    return true;
}

CreditsScreen::CreditsScreen() : AUIScreen("CreditsScreen")
{
    width = 0;
    height = 0;
    bool ret = LoadTextureFromFile("Logo.png", &this->imageTexture, &width, &height);
    IM_ASSERT(ret);
}

CreditsScreen::~CreditsScreen()
{
	AUIScreen::~AUIScreen();
}

void CreditsScreen::drawUI()
{
	ImGui::Begin("Credits");
	ImGui::Text("Engine Version: v0.0.1");
	ImGui::Text("Developer: Roi Tristan A. Nanawa");
	ImGui::NewLine();

    ImGui::Image((void*)this->imageTexture, ImVec2(140, 160));
	
	ImGui::Text("Acknwledgements:");
	ImGui::Text("PardCode");
	ImGui::Text("Sir Neil");
	ImGui::NewLine();
	
	if(ImGui::Button("Close"))
	{
		UIManager::getInstance()->deleteUIScreen(this);
	}

	ImGui::End();
}
