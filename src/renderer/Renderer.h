#ifndef RENDERER_H
#define RENDERER_H 

class Entity;

class Renderer
{
    public:

        Renderer();

        int init();

        int render(const std::vector<Entity*>&);

    private:

        struct impl;
        impl* pimpl;
};

#endif // RENDERER_H
