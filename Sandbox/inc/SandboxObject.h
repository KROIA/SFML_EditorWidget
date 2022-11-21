#pragma once

#include "QSFML_EditorWidget.h"

class SandboxObject: public QObject, public QSFML::Objects::CanvasObject
{
        Q_OBJECT
    public:
    SandboxObject(const std::string &name = "SandboxObject");
    SandboxObject(const SandboxObject &other);
    ~SandboxObject();
    CLONE_FUNC(SandboxObject)

    void update() override;

    private slots:
    void onButtonPress();

    protected:

    private:
        QSFML::Components::DrawableVector *m_vec;

};
