/* This file is part of the KDE project
 * Copyright (C) 2011 Smit Patel <smitpatel24@gmail.com>

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */
#ifndef TOCBIBGENERATORINFO_H
#define TOCBIBGENERATORINFO_H

#include <KoXmlReader.h>
#include <KoXmlWriter.h>
#include <KoText.h>

const int INVALID_OUTLINE_LEVEL = 0;

class BibliographyGenerator;
class ToCGenerator;

class IndexEntry
{
public:
    enum IndexEntryName {UNKNOWN, LINK_START, CHAPTER, SPAN, TEXT, TAB_STOP, PAGE_NUMBER, LINK_END, BIBLIOGRAPHY};

    IndexEntry(QString _styleName, IndexEntryName _name = IndexEntry::UNKNOWN);
    virtual ~IndexEntry();
    virtual void addAttributes(KoXmlWriter * writer) const;
    void saveOdf(KoXmlWriter * writer) const;

    QString styleName;
    IndexEntryName name;
};


class IndexEntryLinkStart : public IndexEntry
{
public:
    IndexEntryLinkStart(QString _styleName);

};


class IndexEntryChapter : public IndexEntry
{
public:
    IndexEntryChapter(QString _styleName);
    virtual void addAttributes(KoXmlWriter* writer) const;

    QString display;
    int outlineLevel;
};


class IndexEntrySpan : public IndexEntry
{
public:
    IndexEntrySpan(QString _styleName);
    virtual void addAttributes(KoXmlWriter* writer) const;

    QString text;
};


class IndexEntryText : public IndexEntry
{
public:
    IndexEntryText(QString _styleName);
};


class IndexEntryTabStop : public IndexEntry
{
public:
    IndexEntryTabStop(QString _styleName);
    virtual void addAttributes(KoXmlWriter* writer) const;
    // for saving let's save the original unit,
    // for KoText::Tab we need to covert to PostScript points
    void setPosition(const QString &position);

    KoText::Tab tab;
    QString m_position;
};


class IndexEntryPageNumber : public IndexEntry
{
public:
    IndexEntryPageNumber(QString _styleName);
};


class IndexEntryLinkEnd : public IndexEntry
{
public:
    IndexEntryLinkEnd(QString _styleName);
};

class TocEntryTemplate
{
public:
    void saveOdf(KoXmlWriter * writer) const;

    int outlineLevel;
    QString styleName;
    int styleId;
    QList<IndexEntry*> indexEntries;
};


class IndexTitleTemplate
{
public:
    void saveOdf(KoXmlWriter * writer) const;

    QString styleName;
    int styleId;
    QString text;
};


class IndexSourceStyle
{
public:
    void saveOdf(KoXmlWriter * writer) const;

    QString styleName;
    int styleId;
};


class IndexSourceStyles
{
public:
    void saveOdf(KoXmlWriter * writer) const;

    int outlineLevel;
    QList<IndexSourceStyle> styles;
};

class IndexEntryBibliography : public IndexEntry
{
public:
    IndexEntryBibliography(QString _styleName);
    virtual void addAttributes(KoXmlWriter* writer) const;

    QString dataField;
};

class BibliographyEntryTemplate
{
public:
    void saveOdf(KoXmlWriter * writer) const;

    QString styleName;
    int styleId;
    QList<IndexEntry*> indexEntries;
    QString bibliographyType;
};

#endif // TOCBIBGENERATORINFO_H
