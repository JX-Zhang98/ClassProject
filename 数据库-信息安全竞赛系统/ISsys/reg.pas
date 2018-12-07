unit reg;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, jpeg, ExtCtrls, IdHashMessageDigest, DB, ADODB;

type
  Tregist = class(TForm)
    Confirm: TButton;
    usr: TEdit;
    email: TEdit;
    psd: TEdit;
    repsd: TEdit;
    regback: TImage;
    usrname: TLabel;
    regemail: TLabel;
    passwd: TLabel;
    repasswd: TLabel;
    proc: TADOStoredProc;
    procedure ConfirmClick(Sender: TObject);
    procedure usrExit(Sender: TObject);
    procedure emailExit(Sender: TObject);
    procedure psdExit(Sender: TObject);
    procedure repsdExit(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  regist: Tregist;

implementation

{$R *.dfm}
uses log;

function MD5(const str:string):String;
var
    AMD5:TIdHashMessageDigest5;
begin
    AMD5:=TIdHashMessageDigest5.Create;
    Result:=AMD5.HashStringAsHex(str,TEncoding.UTF8);
     AMD5.Free;
end;


procedure Tregist.ConfirmClick(Sender: TObject);
var
res:string;
begin
    if (usr.Text='') Or (email.Text='')
      or (psd.Text='') or (repsd.Text='') then
      begin
         Application.MessageBox('请填入完整信息', '提示', MB_ICONWARNING);
         exit;
      end;
    res := '';
    proc.ProcedureName := 'createStudent';
    proc.Parameters.Clear;
    proc.Close;
    proc.Parameters.CreateParameter('username', ftstring, pdinput, 20, NULL);
    proc.Parameters.CreateParameter('password', ftstring, pdinput, 32, NULL);
    proc.Parameters.CreateParameter('email', ftstring, pdinput, 50, NULL);
    proc.Parameters.CreateParameter('res', ftstring, pdOutput, 20, NULL);
    proc.Parameters[0].Value := usr.Text;
    proc.Parameters[1].Value := MD5(psd.Text);
    proc.Parameters[2].Value := email.Text;
    proc.Parameters[3].Value := res;
    proc.Prepared := true;
    proc.ExecProc;
    res := proc.Parameters.ParamByName('res').Value;
    if res = '注册成功' then
    begin
        Application.MessageBox('登录成功！', '提示', MB_OK);
        regist.free;
        login.ShowModal;
    end;
    if res='该用户名已被使用' then
    begin
        Application.MessageBox('该用户名已被使用！', '提示', MB_ICONWARNING);
        usr.Clear;
        usr.SetFocus;
    end;
end;

procedure Tregist.emailExit(Sender: TObject);
begin
    if pos('@',email.Text)=0 then
    begin
      Application.MessageBox('请输入正确的邮箱', '提示', MB_ICONWARNING);
      email.Clear;
      email.SetFocus;
    end;
end;

procedure Tregist.psdExit(Sender: TObject);
begin
    if Length(psd.Text)<6 then
    begin
      Application.MessageBox('密码过于简单', '提示', MB_ICONWARNING);
      email.Clear;
      email.SetFocus;
    end;

end;

procedure Tregist.repsdExit(Sender: TObject);
begin
    if psd.Text<>repsd.Text then
    begin
      Application.MessageBox('两次密码输入不一致，请重新输入', '提示', MB_ICONWARNING);
      repsd.Clear;
      repsd.SetFocus;
    end;

end;

procedure Tregist.usrExit(Sender: TObject);
begin
    //这里进行初步的用户名密码格式合法性验证
     if pos('--', usr.Text)+pos('''',usr.Text)>0 then
     begin
          Application.MessageBox('含有非法字符'',--','警告', MB_ICONWARNING);
          usr.Clear;
          usr.SetFocus;
     end;
end;


end.
