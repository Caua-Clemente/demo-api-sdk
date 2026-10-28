#pragma once

#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QMouseEvent>

class clickablelabel : public QLabel
{
    Q_OBJECT

public:
    explicit clickablelabel(QWidget* parent = nullptr);

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override;
};

#endif // CLICKABLELABEL_H