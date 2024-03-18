#pragma once

#include "QSFML_EditorWidget.h"

class Pendulum : public QObject, public QSFML::Objects::CanvasObject
{
	Q_OBJECT
	struct PendulumData
	{
		double angle = 0.3;
		double angleVelocity = 0;
		double angleAcceleration = 0;
		double length = 100;
		double damping = 0.01;
		double mass = 1;
		QSFML::VectorMath::Vector2d endPos;
		QSFML::VectorMath::Vector2d lastEndPos;
		QSFML::Components::LinePainter* line = nullptr;
	};
public:
    Pendulum(const std::string& name = "Pendulum",
             CanvasObject* parent = nullptr);

	void setStart(double angle1, double angle2);
	void setLength(double length1, double length2);
	void setDamping(float damping1, float damping2);
	void setLinesEnabled(bool enabled);
    void update() override;


private slots:
	void onMouseFalling();
	void onMouseRessing();
private:
	void updatePendulum(PendulumData& pendulumData, PendulumData *prev, double dt);

	double getAngleAcceleration1(const PendulumData& p1, const PendulumData& p2);
	double getAngleAcceleration2(const PendulumData& p1, const PendulumData& p2);
	double getKineticEnergy(const PendulumData& p, double dt);
	double getPotentialEnergy(const PendulumData& p);
	double getEnergy(const PendulumData& p, double dt);

    QSFML::Components::PointPainter *m_pointPainter;
	QSFML::Components::MousePressEvent *m_mousePressEvent;
	QSFML::Components::Text *m_text = nullptr;
	QSFML::Objects::LineChart *m_chart = nullptr;
	std::vector<float> m_chartData;
    //QSFML::Components::LinePainter *m_linePainters[2];

	static constexpr size_t m_count = 2;
	PendulumData m_pendulumData[m_count];
	const double m_gravity = 9.81f;
	const double m_pendulumRadius = 5;
	QSFML::VectorMath::Vector2d m_origin;

	int m_dragingIndex = -1;
	bool m_linesEnabled = true;
};
