// This file is part of Eigen, a lightweight C++ template library
// for linear algebra. Eigen itself is part of the KDE project.
//
// Copyright (C) 2006-2007 Benoit Jacob <jacob@math.jussieu.fr>
//
// Eigen is free software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation; either version 2 or (at your option) any later version.
//
// Eigen is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along
// with Eigen; if not, write to the Free Software Foundation, Inc., 51
// Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
//
// As a special exception, if other files instantiate templates or use macros
// or functions from this file, or you compile this file and link it
// with other works to produce a work based on this file, this file does not
// by itself cause the resulting work to be covered by the GNU General Public
// License. This exception does not invalidate any other reasons why a work
// based on this file might be covered by the GNU General Public License.

#ifndef EIGEN_BLOCK_H
#define EIGEN_BLOCK_H

template<typename MatrixType, int BlockRows, int BlockCols> class Block
  : public MatrixBase<typename MatrixType::Scalar,
                      Block<MatrixType, BlockRows, BlockCols> >
{
  public:
    typedef typename MatrixType::Scalar Scalar;
    typedef typename MatrixType::Ref MatRef;
    friend class MatrixBase<Scalar, Block<MatrixType, BlockRows, BlockCols> >;
    
    static const int RowsAtCompileTime = BlockRows,
                     ColsAtCompileTime = BlockCols;

    Block(const MatRef& matrix, int startRow, int startCol)
      : m_matrix(matrix), m_startRow(startRow), m_startCol(startCol)
    {
      assert(startRow >= 0 && BlockRows >= 1 && startRow + BlockRows <= matrix.rows()
          && startCol >= 0 && BlockCols >= 1 && startCol + BlockCols <= matrix.rows());
    }
    
    Block(const Block& other)
      : m_matrix(other.m_matrix),
        m_startRow(other.m_startRow), m_startCol(other.m_startCol) {}
    
    EIGEN_INHERIT_ASSIGNMENT_OPERATORS(Block)
    
  private:
    const Block& _ref() const { return *this; }
    int _rows() const { return BlockRows; }
    int _cols() const { return BlockCols; }
    
    Scalar& _write(int row, int col)
    {
      return m_matrix.write(row + m_startRow, col + m_startCol);
    }
    
    Scalar _read(int row, int col) const
    {
      return m_matrix.read(row + m_startRow, col + m_startCol);
    }
    
  protected:
    MatRef m_matrix;
    const int m_startRow, m_startCol;
};

template<typename Scalar, typename Derived>
template<int BlockRows, int BlockCols>
Block<Derived, BlockRows, BlockCols> MatrixBase<Scalar, Derived>
  ::block(int startRow, int startCol) const
{
  return Block<Derived, BlockRows, BlockCols>
    (static_cast<Derived*>(const_cast<MatrixBase*>(this))->ref(), startRow, startCol);
}

#endif // EIGEN_BLOCK_H
