/*
   This file is part of the clang-lazy static checker.

  Copyright (C) 2015 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

  As a special exception, permission is given to link this program
  with any edition of Qt, and distribute the resulting executable,
  without including the source code for Qt in the source distribution.
*/

#ifndef CLAZY_QT4_QSTRING_FROM_ARRAY_H
#define CLAZY_QT4_QSTRING_FROM_ARRAY_H

#include "checkbase.h"
#include <vector>

namespace clang {
class Stmt;
class FixItHint;
class CXXConstructExpr;
class CXXOperatorCallExpr;
class Expr;
class CXXMemberCallExpr;
}

/**
 * Replaces QString(char*) or QString(QByteArray) calls with QString::fromLatin1().
 *
 * Run only in Qt 4 code.
 */
class Qt4_QStringFromArray : public CheckBase
{
public:
    explicit Qt4_QStringFromArray(const std::string &name, const clang::CompilerInstance &ci);
    void VisitStmt(clang::Stmt *stmt) override;
private:
    std::vector<clang::FixItHint> fixCtorCall(clang::CXXConstructExpr *ctorExpr);
    std::vector<clang::FixItHint> fixOperatorCall(clang::CXXOperatorCallExpr *ctorExpr);
    std::vector<clang::FixItHint> fixMethodCallCall(clang::CXXMemberCallExpr *memberExpr);
    std::vector<clang::FixItHint> fixitReplaceWithFromLatin1(clang::CXXConstructExpr *ctorExpr);
    std::vector<clang::FixItHint> fixitInsertFromLatin1(clang::CXXConstructExpr *ctorExpr);
};

#endif