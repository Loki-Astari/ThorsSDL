
TTFont::TTFont(std::string const& fileName, int point)
    : PointerWrapper(TTF_OpenFont(fileName.c_str(), point), "Failed to Create TTF-Font. Did you init Lib_TTF (via the Application object)")
{}

TTFont::~TTFont()
{
    TTF_CloseFont(pointer);
}
