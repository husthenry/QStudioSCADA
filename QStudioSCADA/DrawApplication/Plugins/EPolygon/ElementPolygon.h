﻿#ifndef ELEMENTPOLYGON_H
#define ELEMENTPOLYGON_H

#include <QGraphicsSceneEvent>
#include <QPainter>
#include <QDataStream>
#include "Element.h"
#include "tagcolorlistproperty.h"

class ElementPolygon : public Element
{
public:
    ElementPolygon(const QString &projPath);
    void setClickPosition(QPointF);
    void updateBoundingElement();

    void updateElementProperty(uint id, const QVariant &value);
    void updatePropertyModel();
    void createPropertyList();
    void addNodePoint();
    void removeNodePoint();
    void writeAsXml(QXmlStreamWriter &);
    void readFromXml(const QXmlStreamAttributes &);

    void writeData(QDataStream &out);
    void readData(QDataStream &in);

    enum {Type = PolygonItemType};

    int type() const {
        return Type;
    }

    friend QDataStream &operator<<(QDataStream &out,const ElementPolygon &rect);
    friend QDataStream &operator>>(QDataStream &in,ElementPolygon &rect);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    //void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QPainterPath shape() const;

private:
    void createPath();
    bool hasClickedOn(QPointF pressPoint,QPointF point) const;
    void createPoints();
    QString createPointsXmlString() const;

private:
    static int iLastIndex_;
    QPolygonF polygon;
    QVector <QPointF> points;
    // 关联的变量
    QString szTagSelected_;
    // 填充颜色列表
    QStringList tagColorList_;
    // 填充颜色
    QColor fillColor_;
    // 是否填充颜色
    bool isFill_;
    // 边框宽度
    int borderWidth_;
    // 边框颜色
    QColor borderColor_;
    // 初始可见性
    bool showOnInitial_;

    int clickPoint;

    // ID
    TextProperty *idProperty;
    // 标题
    EmptyProperty *titleProperty;
    // X坐标
    IntegerProperty *xCoordProperty;
    // Y坐标
    IntegerProperty *yCoordProperty;
    // Z坐标
    IntegerProperty *zValueProperty;
    // 选择变量
    ListProperty *tagSelectProperty_;
    // 填充颜色列表
    TagColorListProperty *tagColorListProperty_;
    // 填充颜色
    ColorProperty *fillColorProperty_;
    // 是否填充颜色
    BoolProperty *isFillProperty_;
    // 边框宽度
    IntegerProperty *borderWidthProperty_;
    // 边框颜色
    ColorProperty *borderColorProperty_;
    // 初始可见性
    BoolProperty *showOnInitialProperty_;
    // 旋转角度
    IntegerProperty *angleProperty;

};

#endif // ELEMENTPOLYGON_H
