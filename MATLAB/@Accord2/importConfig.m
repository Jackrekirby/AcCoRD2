function [config] = importConfig(filePath)
    config = jsondecode(fileread(filePath));
end