#include "objects/BackgroundGrid.h"

using namespace QSFML::Objects;

BackgroundGrid::BackgroundGrid(const std::string &name,
                               CanvasObject *parent)
    : CanvasObject(name,parent)
{
    m_draw = new DrawableComp();
    m_draw->m_grid = this;
    setSize(sf::IntRect(0,0,500,500));
    setGridSpacing(10);
    setLineColor({sf::Color(130,130,130),sf::Color(100,100,100)});
    addComponent(m_draw);
}
BackgroundGrid::BackgroundGrid(const BackgroundGrid &other)
    : CanvasObject(other)
{
    m_gridArea = other.m_gridArea;
    m_gridSpacing = other.m_gridSpacing;
    m_alternatingColors = other.m_alternatingColors;

    m_draw = new DrawableComp(*other.m_draw);
    m_draw->m_grid = this;

}
BackgroundGrid::~BackgroundGrid()
{}

void BackgroundGrid::setSize(const sf::IntRect &size)
{
    m_gridArea = size;
}
const sf::IntRect &BackgroundGrid::getSize() const
{
    return m_gridArea;
}
void BackgroundGrid::setLineColor(const std::vector<sf::Color> &alternatingColors)
{
    m_alternatingColors = alternatingColors;
}
const std::vector<sf::Color> &BackgroundGrid::getLineColor() const
{
    return m_alternatingColors;
}
void BackgroundGrid::setGridSpacing(unsigned int spacing)
{
    m_gridSpacing = spacing;
}
unsigned int BackgroundGrid::getGridSpacing() const
{
    return m_gridSpacing;
}
void BackgroundGrid::update()
{

}

BackgroundGrid::DrawableComp::DrawableComp(const std::string &name)
    : Drawable(name)
{
    m_grid = nullptr;
}
BackgroundGrid::DrawableComp::DrawableComp(const Drawable &other)
    : Drawable(other)
{
    m_grid = nullptr;
}
void BackgroundGrid::DrawableComp::draw(sf::RenderTarget& target,
                                        sf::RenderStates states) const
{
    drawGrid(target,m_grid->m_gridArea,m_grid->m_gridSpacing,
             m_grid->m_alternatingColors);
    /*sf::Vector2f start(m_grid->m_gridArea.left,m_grid->m_gridArea.top);
    sf::Vector2f end(m_grid->m_gridArea.left,
                     m_grid->m_gridArea.top+m_grid->m_gridArea.height);
    sf::Vector2f VcurrentStart = start;
    sf::Vector2f VcurrentEnd = end;

    sf::Vector2f HcurrentStart = start;
    sf::Vector2f HcurrentEnd = start + sf::Vector2f(m_grid->m_gridArea.width,0);

    size_t spacing = m_grid->m_gridSpacing;

    size_t verticalCount = m_grid->m_gridArea.height  / spacing;
    size_t horizontalCount = m_grid->m_gridArea.width / spacing;

    for(size_t x=0; x<=horizontalCount; ++x)
    {

        sf::Vertex line[] =
        {
            sf::Vertex(VcurrentStart),
            sf::Vertex(VcurrentEnd)
        };


        VcurrentStart.x += spacing;
        VcurrentEnd.x   += spacing;

        target.draw(line, 2, sf::Lines);
    }
    for(size_t y=0; y<=verticalCount; ++y)
    {
        sf::Vertex line[] =
        {
            sf::Vertex(HcurrentStart),
            sf::Vertex(HcurrentEnd)
        };
        HcurrentStart.y += spacing;
        HcurrentEnd.y   += spacing;

        target.draw(line, 2, sf::Lines);

    }*/
}
void BackgroundGrid::DrawableComp::drawGrid(sf::RenderTarget& target,
                                            const sf::IntRect &area,
                                            unsigned int spacing,
                                            const std::vector<sf::Color> &alternatingColors) const
{
    sf::Vector2f start(area.left,area.top);
    sf::Vector2f end(area.left,
                     area.top+area.height);
    sf::Vector2f VcurrentStart = start;
    sf::Vector2f VcurrentEnd = end;

    sf::Vector2f HcurrentStart = start;
    sf::Vector2f HcurrentEnd = start + sf::Vector2f(area.width,0);


    size_t verticalCount = area.height  / spacing;
    size_t horizontalCount = area.width / spacing;

    size_t colorIndex = 0;
    size_t colorCount = alternatingColors.size();

    for(size_t x=0; x<=horizontalCount; ++x)
    {

        sf::Vertex line[] =
        {
            sf::Vertex(VcurrentStart,alternatingColors[colorIndex]),
            sf::Vertex(VcurrentEnd,alternatingColors[colorIndex])
        };
        colorIndex = (colorIndex+1)%colorCount;


        VcurrentStart.x += spacing;
        VcurrentEnd.x   += spacing;

        target.draw(line, 2, sf::Lines);

    }
    colorIndex = 0;
    for(size_t y=0; y<=verticalCount; ++y)
    {
        sf::Vertex line[] =
        {
            sf::Vertex(HcurrentStart,alternatingColors[colorIndex]),
            sf::Vertex(HcurrentEnd,alternatingColors[colorIndex])
        };
        colorIndex = (colorIndex+1)%colorCount;

        HcurrentStart.y += spacing;
        HcurrentEnd.y   += spacing;

        target.draw(line, 2, sf::Lines);

    }
}
