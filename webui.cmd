@ECHO OFF

SET "WEBUIDIR=%~dp0"
CHDIR "%WEBUIDIR%"

IF NOT EXIST stable-diffusion-webui-amdgpu/ (
	git clone --depth 1 https://github.com/lshqqytiger/stable-diffusion-webui-amdgpu.git
)

SET "COMMANDLINE_ARGS=--opt-sub-quad-attention --lowvram --disable-nan-check --use-zluda"
SET "HIP_PATH=%WEBUIDIR%\AMD\ROCm\5.7\"
SET "HIP_PATH_57=%WEBUIDIR%\AMD\ROCm\5.7\"
SET "Path=%WEBUIDIR%\AMD\ROCm\5.7\bin;%WEBUIDIR%\zluda;%Path%"
SET "PYTORCH_CUDA_ALLOC_CONF=expandable_segments:True"

CHDIR .\WPy64-310111\scripts
CALL ".\env_for_icons.bat"

CHDIR "%WEBUIDIR%\stable-diffusion-webui-amdgpu"

zluda.exe -- .\webui.bat
