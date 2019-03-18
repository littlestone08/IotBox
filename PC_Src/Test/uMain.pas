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
    AllocBy := 0;                                //设置总共的项数量，省去每次添加开辟内存空间
    Checkboxes := False;                         //项左边出现复选框，vsList or vsReport有效
    Color := clWindow;                           //背景颜色
    ColumnClick := True;                         //列头能否点击
    with Columns.Add do                          //增加列
    begin
      Alignment := taLeftJustify;                //左对齐
      Caption := '列一';
      ImageIndex := -1;
      Width := 100;
    end;
    with Columns.Add do                          //增加列
    begin
      Caption := '列二';
      ImageIndex := -1;
      Width := 50;
    end;
    Ctl3D := True;
    DoubleBuffered := False;                     //双缓冲
    Enabled := True;
    FlatScrollBars := False;                     //平滑滚动条
    FullDrag := False;                           //允许拖动列头
    GridLines := False;                          //表格线
    GroupHeaderImages := nil;                    //分组头关联图像列表
    with Groups.Add do                           //增加分组
    begin
      Subtitle := '底部的说明文字';
      //BottomDescription := '底部的说明文字';
      //ExtendedImage := -1;                       //关联 GroupHeaderImages图像列表，only on Windows Vista
      TitleImage:= -1;
      Footer := '页脚文本';
      FooterAlign := taLeftJustify;              //页脚文本对齐
      GroupID := 0;                              //组ID号
      Header := '页首文本';
      HeaderAlign := taLeftJustify;
      State := [                                 //分组状态，一些状态只应用于VISTA系统
                lgsNormal,                       //所有分组展开
                lgsHidden,                       //分组隐藏
                lgsCollapsed,                    //分组折叠 Windows Vista only.
                lgsNoHeader,                     //页首不可见 Windows Vista only.
                lgsCollapsible,                  //分组可折叠 Windows Vista only.
                lgsFocused,                      //分组有键盘焦点 Windows Vista only.
                lgsSelected,                     //分组被选择 Windows Vista only.
                lgsSubseted,                     //只有分组的一个子集显示出来 Windows Vista only.
                lgsSubSetLinkFocused             //分组的子集有键盘焦点  Windows Vista only.
               ];
       //SubsetTitle := '子集标题';
       Subtitle := '子标题';
       TitleImage := -1;                         //关联 GroupHeaderImages图像列表，only on Windows Vista
       //TopDescription := '顶部的说明文字';
       Header:= '顶部的说明文字';;
    end;
    with Groups.Add do
    begin
      GroupID := 1;
      Header := '分组标题1';
      Subtitle:= '分组子标题';
      Footer:= '分组底标题1';
      FooterAlign:= taRightJustify;

    end;

    with Groups.Add do
    begin
      GroupID := 2;
      Header := '分组标题2';
      Subtitle:= '分组子标题';
      Footer:= '分组底标题2';
      FooterAlign:= taRightJustify;
    end;
    GroupView := True;                            //打开或关闭分组视图
    HideSelection := True;                        //失去焦点时，项不再保持被选择状态
    HotTrack := False;                            //指定是否鼠标移过项进行高亮
    HotTrackStyles := [
                   //  htHandPoint,               //手势
                   //  htUnderlineCold,           //非热点下划线
                   //  htUnderlineHot             //下划线热点
                      ];
    HoverTime := -1;                              //鼠标在项上暂停时间，除非HotTrack为True
    with IconOptions do                           //确定如何排列图标，vsIcon or vsSmallIcons 有效
    begin
      Arrangement := TIconArrangement.iaTop;                       //项在顶部从左到右对齐，iaLeft在左部从上到下对齐
      AutoArrange := False;                       //图标自动重新排列
      WrapText := True;                           //图标标题是否折行
    end;
    with Items.Add do                             //增加项
    begin
      Caption := '行一列一';
      ImageIndex := -1;                           //关联 LargeImages or SmallImages图像列表
      StateIndex := -1;                           //关联StateImages图像列表
      GroupID := 1;                               //关联分组ID号
      SubItems.Add('行一列二');                   //添加第二列
    end;
    with Items.Add do
    begin
      Caption := '行二列一';
      GroupID := 2;
      SubItems.Add('行二列二');
    end;
    with Items.Add do
    begin
      Caption := '行三列一';
      GroupID := 2;
      SubItems.Add('行三列二');
    end;
    LargeImages := nil;                            //大图标图像列表
    MultiSelect := False;                          //多选
    OwnerData := False;                            //指定列表视图控件是否是虚拟的
    OwnerDraw := False;                            //自绘项
    ParentColor := False;                          //继承父控件颜色
    ReadOnly := False;                             //只读
    RowSelect := False;                            //整行选择
    ShowColumnHeaders := True;                     //显示列头，vsReport有效
    ShowWorkAreas := False;                        //显示工作区，vsIcon or vsSmallIcon有效，不支持 OwnerData
    SmallImages := nil;                            //小图标图像列表
    SortType := stNone;                            //确定列表项如何自动排序
    StateImages := nil;                            //状态图像列表
    ViewStyle := vsReport;                         //视图风格，vsIcon、vsSmallIcon、vsList、vsReport
  end;
end;


procedure TForm1.lv1CustomDrawSubItem(Sender: TCustomListView; Item: TListItem;
  SubItem: Integer; State: TCustomDrawState; var DefaultDraw: Boolean);
begin
  if Item.Caption = '行三列一' then
    Sender.Canvas.Font.Color:= clRed;

end;

end.
