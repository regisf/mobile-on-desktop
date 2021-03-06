; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "Mobile On Desktop"
#define MyAppVersion "0.1"
#define MyAppPublisher "R�gis FLORET"
#define MyAppURL "http://mobile-on-desktop.googlecode.com/"
#define MyAppExeName "mobileondesktop.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{0216431B-647D-4AE7-A756-D3F0ADA29664}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
LicenseFile=..\..\LICENSE.txt
OutputBaseFilename=setup
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1

[Files]
Source: "C:\Users\Regis\Downloads\MobileOnDesktop-build-desktop\release\mobileondesktop.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Regis\Downloads\MobileOnDesktop-build-desktop\release\libstdc++-6.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Regis\Downloads\MobileOnDesktop-build-desktop\release\mingwm10.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Regis\Downloads\MobileOnDesktop-build-desktop\release\phonon4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Regis\Downloads\MobileOnDesktop-build-desktop\release\QtCore4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Regis\Downloads\MobileOnDesktop-build-desktop\release\QtGui4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Regis\Downloads\MobileOnDesktop-build-desktop\release\QtNetwork4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Regis\Downloads\MobileOnDesktop-build-desktop\release\QtWebKit4.dll"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, "&", "&&")}}"; Flags: nowait postinstall skipifsilent

