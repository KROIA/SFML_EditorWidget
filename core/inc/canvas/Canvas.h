#pragma once

#include "QSFML_base.h"
#include "canvas/CanvasSettings.h"
#include "canvas/CanvasObjectContainer.h"

#include "utilities/Timer.h"
#include "utilities/Stats.h"

#include <SFML/Graphics.hpp>
#include <QWidget>
#include <QTimer>


namespace QSFML
{

class QSFML_EDITOR_WIDGET_EXPORT Canvas :
        public QWidget,
        public CanvasObjectContainer,
        public Utilities::StatsManager
    {
        Q_OBJECT
        friend CanvasObjectContainer;
    public:


        Canvas(QWidget* parent, const CanvasSettings &settings = CanvasSettings());

        virtual ~Canvas();


        void setSettings(const CanvasSettings &settings);
        const CanvasSettings &getSettings() const;
        void setLayout(const CanvasSettings::Layout &layout);
        const CanvasSettings::Layout getLayout() const;
        void setTiming(const CanvasSettings::Timing &timing);
        const CanvasSettings::Timing &getTiming() const;
        void setContextSettings(const sf::ContextSettings &contextSettings);
        const sf::ContextSettings &getContextSettings() const;
        void setUpdateControlls(const CanvasSettings::UpdateControlls &controlls);
        const CanvasSettings::UpdateControlls &getUpdateControlls() const;

        void start();
        void stop();

        void setCameraView(const sf::View &view);
        const sf::View &getCameraView() const;
        const sf::View &getDefaultCameraView() const;
        Utilities::AABB getCameraViewRect() const;
        sf::Vector2u getCanvasSize() const;
        sf::Vector2u getOldCanvasSize() const;

        sf::Vector2i getMousePosition() const;
        sf::Vector2f getMouseWorldPosition() const;
        sf::Vector2f getInWorldSpace(const sf::Vector2i &pixelSpace);
        sf::Vector2i getInScreenSpace(const sf::Vector2f &worldSpace);

        

        void sfEvent(const std::vector<sf::Event> &events);

        const sf::Font &getTextFont() const;
        static void setProfilerOutputFileName(const std::string& fileName);
        static const std::string& getProfilerOutputFileName();
        static void saveProfilerFile();
        static void saveProfilerFile(const std::string &fileName);

        size_t getTick() const; // returns the count of updates done
        double getDeltaT() const; // Gets delta Time in 
        double getFPS() const;

        //static void startEventLoop();
        //static void stopEventLoop();

    protected:
        QPaintEngine* paintEngine() const override;
        void showEvent(QShowEvent*) override;
        void paintEvent(QPaintEvent*) override;

        void resizeEvent(QResizeEvent *event) override;



        virtual void OnInit();
        virtual void OnUpdate();

    private slots:
        
        void update();

    private:

        void internal_event(const std::vector<sf::Event> &events);



        QTimer m_frameTimer;
        TimePoint m_deltaT_t1;

        CanvasSettings m_settings;
        sf::RenderWindow *m_window;
        sf::Vector2u m_oldCanvasSize;
        sf::Font m_textfont;
        sf::View m_view;
        static std::string m_profilerOutputFile;

        static std::vector<Canvas*> s_instances;
    };
}
