unit reg;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, jpeg, ExtCtrls;

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
    procedure ConfirmClick(Sender: TObject);
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





procedure Tregist.ConfirmClick(Sender: TObject);
begin

    login.Show;
end;

end.
