/*
    qgpgmekeylistjob.h

    This file is part of qgpgme, the Qt API binding for gpgme
    Copyright (c) 2004,2008 Klarälvdalens Datakonsult AB
    Copyright (c) 2016 Intevation GmbH

    QGpgME is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of the
    License, or (at your option) any later version.

    QGpgME is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

    In addition, as a special exception, the copyright holders give
    permission to link the code of this program with any edition of
    the Qt library by Trolltech AS, Norway (or with modified versions
    of Qt that use the same license as Qt), and distribute linked
    combinations including the two.  You must obey the GNU General
    Public License in all respects for all of the code used other than
    Qt.  If you modify this file, you may extend this exception to
    your version of the file, but you are not obligated to do so.  If
    you do not wish to do so, delete this exception statement from
    your version.
*/

#ifndef __QGPGME_QGPGMEKEYLISTJOB_H__
#define __QGPGME_QGPGMEKEYLISTJOB_H__

#include "keylistjob.h"

#include "threadedjobmixin.h"

#ifdef BUILDING_QGPGME
# include "keylistresult.h"
#else
#include <gpgme++/keylistresult.h>
#endif
#ifdef BUILDING_QGPGME
# include "key.h"
#else
#include <gpgme++/key.h>
#endif

namespace QGpgME
{

class QGpgMEKeyListJob
#ifdef Q_MOC_RUN
    : public KeyListJob
#else
    : public _detail::ThreadedJobMixin<KeyListJob, std::tuple<GpgME::KeyListResult, std::vector<GpgME::Key>, QString, GpgME::Error> >
#endif
{
    Q_OBJECT
#ifdef Q_MOC_RUN
public Q_SLOTS:
    void slotFinished();
#endif
public:
    explicit QGpgMEKeyListJob(GpgME::Context *context);
    ~QGpgMEKeyListJob();

    /*! \reimp from KeyListJob */
    GpgME::Error start(const QStringList &patterns, bool secretOnly) Q_DECL_OVERRIDE;

    /*! \reimp from KeyListJob */
    GpgME::KeyListResult exec(const QStringList &patterns, bool secretOnly, std::vector<GpgME::Key> &keys) Q_DECL_OVERRIDE;

    /*! \reimp from ThreadedJobMixin */
    void resultHook(const result_type &result) Q_DECL_OVERRIDE;

private:
    GpgME::KeyListResult mResult;
    bool mSecretOnly;
};

}

#endif // __QGPGME_QGPGMEKEYLISTJOB_H__
