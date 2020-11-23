Attribute VB_Name = "Modul1"
Sub excel2array()
Attribute excel2array.VB_ProcData.VB_Invoke_Func = " \n14"

    Dim matrix
    
    spalte_max = 36
    zeile_max = 16
    
    matrix = "int matrix[" & spalte_max & "][" & zeile_max & "] = {{"
   
    For icol = 1 To spalte_max
      For irow = 1 To zeile_max
        If Cells(irow, icol).Value = "" Then    'empty field means no LED -> -1
            feld = -1
        Else
            feld = Cells(irow, icol).Value
        End If
        matrix = matrix & feld
        If irow < zeile_max Then matrix = matrix & ","  'no comma after last entry
        Debug.Print feld
      Next irow
      matrix = matrix & "},{"
    Next icol
    
    matrix = matrix & "}};"
    
    Cells(zeile_max + 2, 1).Value = matrix

End Sub
