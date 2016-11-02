Attribute VB_Name = "Module1"
Dim T As Integer
Dim N, M As Integer
Dim A() As Integer
Dim sortA() As Integer
Dim sortB() As Integer
Dim B() As Integer
Dim B2() As Integer
Dim SUM As Integer
Sub sort()
    Dim Temp As Integer
    
    For i = 1 To N
        sortA(i) = A(i)
    Next i
    
    For i = 1 To M
        sortB(i) = B(i)
    Next i
    
    
    For i = 1 To N - 1
        For j = i + 1 To N
            If sortA(i) > sortA(j) Then
                Temp = sortA(i)
                sortA(i) = sortA(j)
                sortA(j) = Temp
            End If
            
        Next j
    Next i
    
    For i = 1 To M - 1
        For j = i + 1 To M
            
            If sortB(i) > sortB(j) Then
                Temp = sortB(i)
                sortB(i) = sortB(j)
                sortB(j) = Temp
            End If
            
        Next j
    Next i
    
    
End Sub
Sub Main()
    Call inp
    Call sort
    SUM = 0
    Call process
    Call out
End Sub
Sub process()

    Dim tmpsum As Integer
    Dim g As Integer
    Dim fg As Integer
    Dim Temp As Integer
    
    tmpsum = 0
    g = 0
    For i = 1 To N
        tmpsum = tmpsum + sortA(i)
        fg = sortA(i)
        sortA(i) = 0
        g = g + 1
        If tmpsum = T Then
            
            Exit For
        ElseIf tmpsum > T Then
            sortA(i) = fg
            g = g - 1
            
            Exit For
        End If
    Next i
    SUM = SUM + g

    fg = 0
    
    'CA에 안들어간것과 남은것을 모두 B2()로 넣는것
    For i = 1 To N
        If sortA(i) <> 0 Then
            fg = fg + 1
            B2(fg) = sortA(i)
        End If
    Next i
    
    For i = 1 To M
        If sortB(i) <> 0 Then
            fg = fg + 1
            B2(fg) = sortB(i)
        End If
    Next i
    
    '다시 정렬
    For i = 1 To fg - 1
        For j = i + 1 To fg
            If B2(i) > B2(j) Then
                Temp = B2(i)
                B2(i) = B2(j)
                B2(j) = Temp
            End If
        Next j
    Next i
    

    
    tmpsum = 0
    g = 0
    For i = 1 To fg
        tmpsum = tmpsum + B2(i)
        Temp = B2(i)
        B2(i) = 0
        g = g + 1
        If tmpsum = T Then

            Exit For
        ElseIf tmpsum > T Then
            sortA(i) = fg
            g = g - 1

            Exit For
        End If
    Next i
    SUM = SUM + g

    
    

    
End Sub
Sub inp()
    Dim f As Integer
    Dim fg As Integer
    
    f = FreeFile()
    
    Open "delivery.in" For Input As f
        Input #f, T
        Input #f, N
        ReDim A(1 To N) As Integer
        ReDim sortA(N) As Integer
        For i = 1 To N
            Input #f, A(i)
        Next i
        
        Input #f, M
        ReDim B(1 To M) As Integer
        ReDim sortB(M) As Integer
        For i = 1 To M
            Input #f, B(i)
        Next i
        
        fg = N + M
        ReDim B2(fg) As Integer
        
    Close f
    
End Sub
Sub out()
    Dim f As Integer
    f = FreeFile()
    Open "delivery.out" For Output As f
        Print #f, SUM
    Close f
End Sub
