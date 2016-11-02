object Form1: TForm1
  Left = 192
  Top = 107
  Width = 163
  Height = 197
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = '宋体'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 12
  object Label1: TLabel
    Left = 8
    Top = 24
    Width = 36
    Height = 12
    Caption = '测试点'
  end
  object Label2: TLabel
    Left = 8
    Top = 56
    Width = 48
    Height = 12
    Caption = '标准答案'
  end
  object Label3: TLabel
    Left = 8
    Top = 80
    Width = 48
    Height = 12
    Caption = '待测答案'
  end
  object lblResult: TLabel
    Left = 8
    Top = 144
    Width = 60
    Height = 12
    Caption = '比较结果：'
  end
  object UpDown1: TUpDown
    Left = 65
    Top = 16
    Width = 15
    Height = 20
    Associate = edtPoint
    Min = 0
    Max = 9
    Position = 0
    TabOrder = 0
    Wrap = False
    OnChangingEx = UpDown1ChangingEx
  end
  object edtStandard: TEdit
    Left = 64
    Top = 48
    Width = 73
    Height = 20
    TabOrder = 1
    Text = 'markov.ou0'
  end
  object edtTest: TEdit
    Left = 64
    Top = 72
    Width = 73
    Height = 20
    TabOrder = 2
    Text = 'markov.out'
  end
  object Button1: TButton
    Left = 40
    Top = 104
    Width = 75
    Height = 25
    Caption = '开始比较'
    TabOrder = 3
    OnClick = Button1Click
  end
  object edtPoint: TEdit
    Left = 48
    Top = 16
    Width = 17
    Height = 20
    TabOrder = 4
    Text = '0'
  end
end
