#include "surfacegraph.h"

const int treeCount = 10;

SurfaceGraph::SurfaceGraph(Q3DSurface *surface) : m_graph(surface), m_uniform_distribution(false), m_normal_distribution(false), m_unbalanced_distribution(false){
    m_graph->setOrthoProjection(true);
    m_graph->axisX()->setRange(0.0f, 1.0f);
    m_graph->axisX()->setTitle(QStringLiteral("x = data count"));
    m_graph->axisX()->setTitleVisible(true);
    m_graph->axisX()->setLabelAutoRotation(90);

    m_graph->axisY()->setRange(0.0f, 1.0f);
    m_graph->axisY()->setTitle(QStringLiteral("y = worst time to find the most depp element"));
    m_graph->axisY()->setTitleVisible(true);
    m_graph->axisY()->setLabelAutoRotation(90);

    m_graph->axisZ()->setRange(0.0f, 1.0f);
    m_graph->axisZ()->setTitle(QStringLiteral("z = operation count"));
    m_graph->axisZ()->setTitleVisible(true);
    m_graph->axisZ()->setLabelAutoRotation(90);

    m_uniform_proxy = new QSurfaceDataProxy();
    m_uniform_series = new QSurface3DSeries(m_uniform_proxy);
    m_uniform_proxy_xy = new QSurfaceDataProxy();
    m_uniform_series_xy = new QSurface3DSeries(m_uniform_proxy_xy);
    m_uniform_proxy_xz = new QSurfaceDataProxy();
    m_uniform_series_xz = new QSurface3DSeries(m_uniform_proxy_xz);
    m_uniform_proxy_yz = new QSurfaceDataProxy();
    m_uniform_series_yz = new QSurface3DSeries(m_uniform_proxy_yz);

    m_normal_proxy = new QSurfaceDataProxy();
    m_normal_series = new QSurface3DSeries(m_normal_proxy);
    m_normal_proxy_xy = new QSurfaceDataProxy();
    m_normal_series_xy = new QSurface3DSeries(m_normal_proxy_xy);
    m_normal_proxy_xz = new QSurfaceDataProxy();
    m_normal_series_xz = new QSurface3DSeries(m_normal_proxy_xz);
    m_normal_proxy_yz = new QSurfaceDataProxy();
    m_normal_series_yz = new QSurface3DSeries(m_normal_proxy_yz);

    m_unbalanced_proxy = new QSurfaceDataProxy();
    m_unbalanced_series = new QSurface3DSeries(m_unbalanced_proxy);
    m_unbalanced_proxy_xy = new QSurfaceDataProxy();
    m_unbalanced_series_xy = new QSurface3DSeries(m_unbalanced_proxy_xy);
    m_unbalanced_proxy_xz = new QSurfaceDataProxy();
    m_unbalanced_series_xz = new QSurface3DSeries(m_unbalanced_proxy_xz);
    m_unbalanced_proxy_yz = new QSurfaceDataProxy();
    m_unbalanced_series_yz = new QSurface3DSeries(m_unbalanced_proxy_yz);

    m_tree_uniform = new Tree*[treeCount];
    m_tree_normal = new Tree*[treeCount];
    m_tree_unbalanced = new Tree*[treeCount];
    for(int i = 0; i < treeCount; i++){
        m_tree_uniform[i] = new Tree;
        m_tree_normal[i] = new Tree;
        m_tree_unbalanced[i] = new Tree;
    }
}

SurfaceGraph::~SurfaceGraph(){
    delete m_graph;
    for(int i = 0; i < treeCount; i++){
        delete m_tree_uniform[i];
        delete m_tree_normal[i];
        delete m_tree_unbalanced[i];
    }
    delete[] m_tree_uniform;
    delete[] m_tree_normal;
    delete[] m_tree_unbalanced;
}

void SurfaceGraph::fill_proxy(Tree **tree, QSurfaceDataProxy *xyz, QSurfaceDataProxy *xy, QSurfaceDataProxy *xz, QSurfaceDataProxy *yz){
    double stepX = tree[treeCount - 1]->get_count() / (double)(tree[treeCount - 1]->get_count() - 1);
    double stepZ = tree[treeCount - 1]->get_count() / (double)(tree[treeCount - 1]->get_length() - 1);
    QSurfaceDataArray *dataArray = new QSurfaceDataArray;
    QSurfaceDataArray *dataArray_xy = new QSurfaceDataArray;
    QSurfaceDataArray *dataArray_xz = new QSurfaceDataArray;
    QSurfaceDataArray *dataArray_yz = new QSurfaceDataArray;
    dataArray->reserve(treeCount);
    dataArray_xy->reserve(treeCount);
    dataArray_xz->reserve(treeCount);
    dataArray_yz->reserve(treeCount);
    for (int i = 0 ; i < treeCount ; i++) {
        QSurfaceDataRow *newRow = new QSurfaceDataRow(treeCount);
        QSurfaceDataRow *newRow_xy = new QSurfaceDataRow(treeCount);
        QSurfaceDataRow *newRow_xz = new QSurfaceDataRow(treeCount);
        QSurfaceDataRow *newRow_yz = new QSurfaceDataRow(treeCount);
        float x, y, z;
        if(tree[treeCount - 1]->get_count()){
            x = qMin((double)tree[treeCount - 1]->get_count(), tree[i]->get_count() * stepX);
        }
        else{
            x = qMin((double)tree[treeCount - 1]->get_count(), tree[i]->get_count() * stepX);
        }
        int index = 0;
        for(int j = 0; j < treeCount; j++){
            if(tree[treeCount - 1]->get_worst_time()){
                y = qMin(tree[treeCount - 1]->get_worst_time(), tree[i]->get_worst_time());
            }
            else{
                y = qMin(tree[treeCount - 1]->get_worst_time(), tree[i]->get_worst_time());
            }
            if(tree[treeCount - 1]->get_count()){
                z = qMin((double)tree[treeCount - 1]->get_count(), tree[i]->get_length() * stepZ);
            }
            else{
                z = qMin((double)tree[treeCount - 1]->get_count(), tree[i]->get_length() * stepZ);
            }
            (*newRow)[index++].setPosition(QVector3D(x, y, z));
            (*newRow_xy)[index-1].setPosition(QVector3D(x, y, tree[treeCount - 1]->get_count()));
            (*newRow_xz)[index-1].setPosition(QVector3D(x, 0, z));
            (*newRow_yz)[index-1].setPosition(QVector3D(0, y, z));
        }
        *dataArray << newRow;
        *dataArray_xy << newRow_xy;
        *dataArray_xz << newRow_xz;
        *dataArray_yz << newRow_yz;
    }
    xyz->resetArray(dataArray);
    xy->resetArray(dataArray_xy);
    xz->resetArray(dataArray_xz);
    yz->resetArray(dataArray_yz);
}

void SurfaceGraph::enable_uniform_distribution(bool enable){
    if(enable){
        if(m_normal_distribution){
            m_graph->removeSeries(m_normal_series);
            m_graph->removeSeries(m_normal_series_xy);
            m_graph->removeSeries(m_normal_series_xz);
            m_graph->removeSeries(m_normal_series_yz);
            m_normal_distribution = false;
        }
        if(m_unbalanced_distribution){
            m_graph->removeSeries(m_unbalanced_series);
            m_graph->removeSeries(m_unbalanced_series_xy);
            m_graph->removeSeries(m_unbalanced_series_xz);
            m_graph->removeSeries(m_unbalanced_series_yz);
            m_unbalanced_distribution = false;
        }
        m_uniform_distribution = true;

        m_uniform_series->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
        m_uniform_series->setFlatShadingEnabled(true);
        m_uniform_series->setBaseColor(QColor(100, 0, 0, 255));

        m_graph->addSeries(m_uniform_series);
        m_graph->addSeries(m_uniform_series_xy);
        m_graph->addSeries(m_uniform_series_xz);
        m_graph->addSeries(m_uniform_series_yz);

        if(m_tree_unbalanced[treeCount - 1]->get_count() > 1.0f){
            m_graph->axisX()->setRange(0.0f, m_tree_unbalanced[treeCount - 1]->get_count());
            m_graph->axisZ()->setRange(0.0f, m_tree_unbalanced[treeCount - 1]->get_count());
        }
        else if(m_tree_uniform[treeCount - 1]->get_count() > 1.0f){
            m_graph->axisX()->setRange(0.0f, m_tree_uniform[treeCount - 1]->get_count());
            m_graph->axisZ()->setRange(0.0f, m_tree_uniform[treeCount - 1]->get_count());
        }
        if(m_tree_unbalanced[treeCount - 1]->get_worst_time() > 1.0f){
            m_graph->axisY()->setRange(0.0f, m_tree_unbalanced[treeCount - 1]->get_worst_time());
        }
        else if(m_tree_uniform[treeCount - 1]->get_worst_time() > 1.0f){
            m_graph->axisY()->setRange(0.0f, m_tree_uniform[treeCount - 1]->get_worst_time());
        }
    }
}

void SurfaceGraph::enable_normal_distributinon(bool enable){
    if(enable){
        if(m_uniform_distribution){
            m_graph->removeSeries(m_uniform_series);
            m_graph->removeSeries(m_uniform_series_xy);
            m_graph->removeSeries(m_uniform_series_xz);
            m_graph->removeSeries(m_uniform_series_yz);
            m_uniform_distribution = false;
        }
        if(m_unbalanced_distribution){
            m_graph->removeSeries(m_unbalanced_series);
            m_graph->removeSeries(m_unbalanced_series_xy);
            m_graph->removeSeries(m_unbalanced_series_xz);
            m_graph->removeSeries(m_unbalanced_series_yz);
            m_unbalanced_distribution = false;
        }
        m_normal_distribution = true;

        m_normal_series->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
        m_normal_series->setFlatShadingEnabled(true);

        m_graph->addSeries(m_normal_series);
        m_graph->addSeries(m_normal_series_xy);
        m_graph->addSeries(m_normal_series_xz);
        m_graph->addSeries(m_normal_series_yz);

        if(m_tree_unbalanced[treeCount - 1]->get_count() > 1.0f){
            m_graph->axisX()->setRange(0.0f, m_tree_unbalanced[treeCount - 1]->get_count());
            m_graph->axisZ()->setRange(0.0f, m_tree_unbalanced[treeCount - 1]->get_count());
        }
        else if(m_tree_normal[treeCount - 1]->get_count() > 1.0f){
            m_graph->axisX()->setRange(0.0f, m_tree_normal[treeCount - 1]->get_count());
            m_graph->axisZ()->setRange(0.0f, m_tree_normal[treeCount - 1]->get_count());
        }
        if(m_tree_unbalanced[treeCount - 1]->get_worst_time() > 1.0f){
            m_graph->axisY()->setRange(0.0f, m_tree_unbalanced[treeCount - 1]->get_worst_time());
        }
        else if(m_tree_normal[treeCount - 1]->get_worst_time() > 1.0f){
            m_graph->axisY()->setRange(0.0f, m_tree_normal[treeCount - 1]->get_worst_time());
        }
    }
}

void SurfaceGraph::enable_unbalanced_distribution(bool enable){
    if(enable){
        if(m_uniform_distribution){
            m_graph->removeSeries(m_uniform_series);
            m_graph->removeSeries(m_uniform_series_xy);
            m_graph->removeSeries(m_uniform_series_xz);
            m_graph->removeSeries(m_uniform_series_yz);
            m_uniform_distribution = false;
        }
        if(m_normal_distribution){
            m_graph->removeSeries(m_normal_series);
            m_graph->removeSeries(m_normal_series_xy);
            m_graph->removeSeries(m_normal_series_xz);
            m_graph->removeSeries(m_normal_series_yz);
            m_normal_distribution = false;
        }
        m_unbalanced_distribution = true;

        m_unbalanced_series->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
        m_unbalanced_series->setFlatShadingEnabled(true);

        m_graph->addSeries(m_unbalanced_series);
        m_graph->addSeries(m_unbalanced_series_xy);
        m_graph->addSeries(m_unbalanced_series_xz);
        m_graph->addSeries(m_unbalanced_series_yz);

        if(m_tree_unbalanced[treeCount - 1]->get_count() > 1.0f){
            m_graph->axisX()->setRange(0.0f, m_tree_unbalanced[treeCount - 1]->get_count());
            m_graph->axisZ()->setRange(0.0f, m_tree_unbalanced[treeCount - 1]->get_count());
        }
        if(m_tree_unbalanced[treeCount - 1]->get_worst_time() > 1.0f){
            m_graph->axisY()->setRange(0.0f, m_tree_unbalanced[treeCount - 1]->get_worst_time());
        }
    }
}

void SurfaceGraph::generate_new_tree(){
    if(m_uniform_distribution){
            for(int i = 0; i < treeCount; i++){
                m_tree_uniform[i]->reset(Distribution::UNIFORM);
                for(int j = 0; j < pow(2, i + 1) * treeCount; j++){
                    m_tree_uniform[i]->insert(j);
                }
                m_tree_uniform[i]->update_length();
                m_tree_uniform[i]->update_worst_time();
            }
            fill_proxy(m_tree_uniform, m_uniform_proxy, m_uniform_proxy_xy, m_uniform_proxy_xz, m_uniform_proxy_yz);
            enable_uniform_distribution(true);
        }
    else if(m_normal_distribution){
        for(int i = 0; i < treeCount; i++){
            m_tree_normal[i]->reset(Distribution::NORMAL);
            for(int j = 0; j < pow(2, i + 1) * treeCount; j++){
                m_tree_normal[i]->insert(j);
            }
            m_tree_normal[i]->update_length();
            m_tree_normal[i]->update_worst_time();
        }
        fill_proxy(m_tree_normal, m_normal_proxy, m_normal_proxy_xy, m_normal_proxy_xz, m_normal_proxy_yz);
        enable_normal_distributinon(true);
    }
    else if(m_unbalanced_distribution){
        for(int i = 0; i < treeCount; i++){
            m_tree_unbalanced[i]->reset(Distribution::UNBALANCED);
            for(int j = 0; j < pow(2, i + 1) * treeCount; j++){
                m_tree_unbalanced[i]->insert(j);
            }
            m_tree_unbalanced[i]->update_length();
            m_tree_unbalanced[i]->update_worst_time();
        }
        fill_proxy(m_tree_unbalanced, m_unbalanced_proxy, m_unbalanced_proxy_xy, m_unbalanced_proxy_xz, m_unbalanced_proxy_yz);
        enable_unbalanced_distribution(true);
    }
}

void SurfaceGraph::enable_axisXY(bool enable){
    if(enable){
        m_graph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetDirectlyBelow);
    }
}

void SurfaceGraph::enable_axisXZ(bool enable){
    if(enable){
        m_graph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetDirectlyAbove);
    }
}

void SurfaceGraph::enable_axisYZ(bool enable){
    if(enable){
        m_graph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetRightLow);
    }
}
