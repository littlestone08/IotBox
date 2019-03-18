unit uMain;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.ComCtrls, Vcl.StdCtrls;

type
  TForm1 = class(TForm)
    lv1: TListView;
    procedure FormCreate(Sender: TObject);
    procedure lv1CustomDrawSubItem(Sender: TCustomListView; Item: TListItem;
      SubItem: Integer; State: TCustomDrawState; var DefaultDraw: Boolean);

  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation


{$R *.dfm}



procedure TForm1.FormCreate(Sender: TObject);
begin
  with lv1 do
  begin
    AllocBy := 0;                                //�����ܹ�����������ʡȥÿ����ӿ����ڴ�ռ�
    Checkboxes := False;                         //����߳��ָ�ѡ��vsList or vsReport��Ч
    Color := clWindow;                           //������ɫ
    ColumnClick := True;                         //��ͷ�ܷ���
    with Columns.Add do                          //������
    begin
      Alignment := taLeftJustify;                //�����
      Caption := '��һ';
      ImageIndex := -1;
      Width := 100;
    end;
    with Columns.Add do                          //������
    begin
      Caption := '�ж�';
      ImageIndex := -1;
      Width := 50;
    end;
    Ctl3D := True;
    DoubleBuffered := False;                     //˫����
    Enabled := True;
    FlatScrollBars := False;                     //ƽ��������
    FullDrag := False;                           //�����϶���ͷ
    GridLines := False;                          //�����
    GroupHeaderImages := nil;                    //����ͷ����ͼ���б�
    with Groups.Add do                           //���ӷ���
    begin
      Subtitle := '�ײ���˵������';
      //BottomDescription := '�ײ���˵������';
      //ExtendedImage := -1;                       //���� GroupHeaderImagesͼ���б�only on Windows Vista
      TitleImage:= -1;
      Footer := 'ҳ���ı�';
      FooterAlign := taLeftJustify;              //ҳ���ı�����
      GroupID := 0;                              //��ID��
      Header := 'ҳ���ı�';
      HeaderAlign := taLeftJustify;
      State := [                                 //����״̬��һЩ״ֻ̬Ӧ����VISTAϵͳ
                lgsNormal,                       //���з���չ��
                lgsHidden,                       //��������
                lgsCollapsed,                    //�����۵� Windows Vista only.
                lgsNoHeader,                     //ҳ�ײ��ɼ� Windows Vista only.
                lgsCollapsible,                  //������۵� Windows Vista only.
                lgsFocused,                      //�����м��̽��� Windows Vista only.
                lgsSelected,                     //���鱻ѡ�� Windows Vista only.
                lgsSubseted,                     //ֻ�з����һ���Ӽ���ʾ���� Windows Vista only.
                lgsSubSetLinkFocused             //������Ӽ��м��̽���  Windows Vista only.
               ];
       //SubsetTitle := '�Ӽ�����';
       Subtitle := '�ӱ���';
       TitleImage := -1;                         //���� GroupHeaderImagesͼ���б�only on Windows Vista
       //TopDescription := '������˵������';
       Header:= '������˵������';;
    end;
    with Groups.Add do
    begin
      GroupID := 1;
      Header := '�������1';
      Subtitle:= '�����ӱ���';
      Footer:= '����ױ���1';
      FooterAlign:= taRightJustify;

    end;

    with Groups.Add do
    begin
      GroupID := 2;
      Header := '�������2';
      Subtitle:= '�����ӱ���';
      Footer:= '����ױ���2';
      FooterAlign:= taRightJustify;
    end;
    GroupView := True;                            //�򿪻�رշ�����ͼ
    HideSelection := True;                        //ʧȥ����ʱ����ٱ��ֱ�ѡ��״̬
    HotTrack := False;                            //ָ���Ƿ�����ƹ�����и���
    HotTrackStyles := [
                   //  htHandPoint,               //����
                   //  htUnderlineCold,           //���ȵ��»���
                   //  htUnderlineHot             //�»����ȵ�
                      ];
    HoverTime := -1;                              //�����������ͣʱ�䣬����HotTrackΪTrue
    with IconOptions do                           //ȷ���������ͼ�꣬vsIcon or vsSmallIcons ��Ч
    begin
      Arrangement := TIconArrangement.iaTop;                       //���ڶ��������Ҷ��룬iaLeft���󲿴��ϵ��¶���
      AutoArrange := False;                       //ͼ���Զ���������
      WrapText := True;                           //ͼ������Ƿ�����
    end;
    with Items.Add do                             //������
    begin
      Caption := '��һ��һ';
      ImageIndex := -1;                           //���� LargeImages or SmallImagesͼ���б�
      StateIndex := -1;                           //����StateImagesͼ���б�
      GroupID := 1;                               //��������ID��
      SubItems.Add('��һ�ж�');                   //��ӵڶ���
    end;
    with Items.Add do
    begin
      Caption := '�ж���һ';
      GroupID := 2;
      SubItems.Add('�ж��ж�');
    end;
    with Items.Add do
    begin
      Caption := '������һ';
      GroupID := 2;
      SubItems.Add('�����ж�');
    end;
    LargeImages := nil;                            //��ͼ��ͼ���б�
    MultiSelect := False;                          //��ѡ
    OwnerData := False;                            //ָ���б���ͼ�ؼ��Ƿ��������
    OwnerDraw := False;                            //�Ի���
    ParentColor := False;                          //�̳и��ؼ���ɫ
    ReadOnly := False;                             //ֻ��
    RowSelect := False;                            //����ѡ��
    ShowColumnHeaders := True;                     //��ʾ��ͷ��vsReport��Ч
    ShowWorkAreas := False;                        //��ʾ��������vsIcon or vsSmallIcon��Ч����֧�� OwnerData
    SmallImages := nil;                            //Сͼ��ͼ���б�
    SortType := stNone;                            //ȷ���б�������Զ�����
    StateImages := nil;                            //״̬ͼ���б�
    ViewStyle := vsReport;                         //��ͼ���vsIcon��vsSmallIcon��vsList��vsReport
  end;
end;


procedure TForm1.lv1CustomDrawSubItem(Sender: TCustomListView; Item: TListItem;
  SubItem: Integer; State: TCustomDrawState; var DefaultDraw: Boolean);
begin
  if Item.Caption = '������һ' then
    Sender.Canvas.Font.Color:= clRed;

end;

end.
