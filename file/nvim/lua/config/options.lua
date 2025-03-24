-- Options are automatically loaded before lazy.nvim startup
-- Default options that are always set: https://github.com/LazyVim/LazyVim/blob/main/lua/lazyvim/config/options.lua
-- Add any additional options here

-- 关闭相对行号
vim.opt.relativenumber = false

-- 设置缩进为4个空格
vim.opt.shiftwidth = 4      -- 设置自动缩进长度为4空格
vim.opt.tabstop = 4         -- 设置tab长度为4空

vim.o.guifont = "Maple Mono:h10"

if vim.g.neovide then
    vim.g.neovide_scale_factor = 1.0

    vim.g.neovide_ligatures = true

    vim.g.neovide_refresh_rate = 144

    vim.o.guifont = "Maple Mono:h12"
end
