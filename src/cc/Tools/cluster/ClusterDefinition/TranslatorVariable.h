/* -*- c++ -*-
 * Copyright (C) 2007-2014 Hypertable, Inc.
 *
 * This file is part of Hypertable.
 *
 * Hypertable is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; version 3 of the
 * License, or any later version.
 *
 * Hypertable is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

/// @file
/// Declarations for TranslatorVariable.
/// This file contains type declarations for TranslatorVariable, a class for
/// translating variable definition statements.

#ifndef Tools_cluster_TranslatorVariable_h
#define Tools_cluster_TranslatorVariable_h

#include "TranslationContext.h"
#include "Translator.h"

#include <string>

namespace Hypertable { namespace ClusterDefinition {

  using namespace std;

  /// @addtogroup ClusterDefinition
  /// @{

  /// Translates a variable definition.
  class TranslatorVariable : public Translator {
  public:
    /// Constructor.
    /// @param fname Filename of source file containing variable definition
    /// @param lineno Line number within source file of variable definition text
    /// @param text Text of variable definition
    TranslatorVariable(const string &fname, size_t lineno, const string &text)
      : m_fname(fname), m_lineno(lineno), m_text(text) {};

    /// Translates a variable definition.
    /// This method doesn't actually do any translation of the variable
    /// definition text, but parses it and adds the variable to the symbol table
    /// in <code>context</code> which is used by downstream translators.
    /// @return Unmodified variable definition text
    const string translate(TranslationContext &context) override;

  private:
    /// Source file name containing input text
    string m_fname;
    /// Starting offset within #m_fname of input text
    size_t m_lineno;
    /// Text of variable definition
    string m_text;
  };

  /// @}

}}

#endif // Tools_cluster_TranslatorVariable_h
