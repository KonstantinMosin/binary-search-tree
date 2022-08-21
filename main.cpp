#include "surfacegraph.h"

#include <QApplication>

int main(int argc, char *argv[]){
    srand(time(NULL));

    QApplication a(argc, argv);

    Q3DSurface *graph = new Q3DSurface();
    QWidget *container = QWidget::createWindowContainer(graph);
    if (!graph->hasContext()) {
        QMessageBox msgBox;
        msgBox.setText("Couldn't initialize the OpenGL context.");
        msgBox.exec();
        return -1;
    }

    QSize screenSize = graph->screen()->size();
    container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.6));
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);
    vLayout->setAlignment(Qt::AlignTop);

    widget->setWindowTitle(QStringLiteral("cw"));

    QGroupBox *modelGroupBox = new QGroupBox(QStringLiteral("Model"));

    QRadioButton *uniform_distribution = new QRadioButton(widget);
    uniform_distribution->setText(QStringLiteral("uniform"));
    uniform_distribution->setChecked(false);

    QRadioButton *normal_distribution = new QRadioButton(widget);
    normal_distribution->setText(QStringLiteral("normal"));
    normal_distribution->setChecked(false);

    QRadioButton *unbalanced_distribution = new QRadioButton(widget);
    unbalanced_distribution->setText(QStringLiteral("unbalanced"));
    unbalanced_distribution->setChecked(false);

    QPushButton *generate = new QPushButton(widget);
    generate->setText(QStringLiteral("generate new tree"));

    QVBoxLayout *modelVBox = new QVBoxLayout;
    modelVBox->addWidget(uniform_distribution);
    modelVBox->addWidget(normal_distribution);
    modelVBox->addWidget(unbalanced_distribution);
    modelVBox->addWidget(generate);
    modelGroupBox->setLayout(modelVBox);

    QGroupBox *axisGroupBox = new QGroupBox(QStringLiteral("Axis"));

    QRadioButton *axisXY = new QRadioButton(widget);
    axisXY->setText(QStringLiteral("axisXY"));
    axisXY->setChecked(false);

    QRadioButton *axisXZ = new QRadioButton(widget);
    axisXZ->setText(QStringLiteral("axisXZ"));
    axisXZ->setChecked(false);

    QRadioButton *axisYZ = new QRadioButton(widget);
    axisYZ->setText(QStringLiteral("axisYZ"));
    axisYZ->setChecked(false);

    QVBoxLayout *axisVBox = new QVBoxLayout;
    axisVBox->addWidget(axisXY);
    axisVBox->addWidget(axisXZ);
    axisVBox->addWidget(axisYZ);
    axisGroupBox->setLayout(axisVBox);

    vLayout->addWidget(modelGroupBox);
    vLayout->addWidget(axisGroupBox);

    widget->show();

    SurfaceGraph *modifier = new SurfaceGraph(graph);

    QObject::connect(uniform_distribution, &QRadioButton::toggled,
                     modifier, &SurfaceGraph::enable_uniform_distribution);
    QObject::connect(normal_distribution, &QRadioButton::toggled,
                     modifier, &SurfaceGraph::enable_normal_distributinon);
    QObject::connect(unbalanced_distribution, &QRadioButton::toggled,
                     modifier, &SurfaceGraph::enable_unbalanced_distribution);
    QObject::connect(generate, &QPushButton::pressed,
                     modifier, &SurfaceGraph::generate_new_tree);
    QObject::connect(axisXY, &QRadioButton::toggled,
                     modifier, &SurfaceGraph::enable_axisXY);
    QObject::connect(axisXZ, &QRadioButton::toggled,
                     modifier, &SurfaceGraph::enable_axisXZ);
    QObject::connect(axisYZ, &QRadioButton::toggled,
                     modifier, &SurfaceGraph::enable_axisYZ);

    uniform_distribution->setChecked(true);
    axisXY->setChecked(true);

    return a.exec();
}
