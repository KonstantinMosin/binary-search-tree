#ifndef SURFACEGRAPH_H
#define SURFACEGRAPH_H

#include <QtWidgets>
#include <QtDataVisualization/Q3DSurface>

#include "tree.h"

using namespace QtDataVisualization;

class SurfaceGraph : public QObject{
    Q_OBJECT
public:
    SurfaceGraph(Q3DSurface *surface);
    ~SurfaceGraph();

    void enable_uniform_distribution(bool enable);
    void enable_normal_distributinon(bool enable);
    void enable_unbalanced_distribution(bool enable);
    void generate_new_tree();

    void enable_axisXY(bool enable);
    void enable_axisXZ(bool enable);
    void enable_axisYZ(bool enable);

private:
    void fill_proxy(Tree **tree, QSurfaceDataProxy *xyz, QSurfaceDataProxy *xy, QSurfaceDataProxy *xz, QSurfaceDataProxy *yz);

private:
    Q3DSurface *m_graph;

    QSurfaceDataProxy *m_uniform_proxy, *m_uniform_proxy_xy, *m_uniform_proxy_xz, *m_uniform_proxy_yz;
    QSurface3DSeries *m_uniform_series, *m_uniform_series_xy, *m_uniform_series_xz, *m_uniform_series_yz;
    bool m_uniform_distribution;

    QSurfaceDataProxy *m_normal_proxy, *m_normal_proxy_xy, *m_normal_proxy_xz, *m_normal_proxy_yz;
    QSurface3DSeries *m_normal_series, *m_normal_series_xy, *m_normal_series_xz, *m_normal_series_yz;
    bool m_normal_distribution;

    QSurfaceDataProxy *m_unbalanced_proxy, *m_unbalanced_proxy_xy, *m_unbalanced_proxy_xz, *m_unbalanced_proxy_yz;
    QSurface3DSeries *m_unbalanced_series, *m_unbalanced_series_xy, *m_unbalanced_series_xz, *m_unbalanced_series_yz;
    bool m_unbalanced_distribution;

    Tree **m_tree_uniform;
    Tree **m_tree_normal;
    Tree **m_tree_unbalanced;
};

#endif // SURFACEGRAPH_H
