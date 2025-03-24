return {
  -- 添加 onedark 插件
  {
    "navarasu/onedark.nvim",
    lazy = false,
    priority = 10,
    config = function()
      require('onedark').setup({
        -- 配置选项
        style = 'darker', -- 可选: dark, darker, cool, deep, warm, warmer
        transparent = false,  -- 启用透明背景
        term_colors = false,
        -- 其他配置选项...
      })
      -- 设置配色方案
      vim.cmd.colorscheme 'onedark'
    end,
  },
  -- 添加 onedarkpro 主题
  {
    "olimorris/onedarkpro.nvim",
    priority = 1000, -- 确保它在其他插件之前加载
    config = function()
      require("onedarkpro").setup({
        -- 您可以在这里添加定制选项
        -- 例如:
        -- colors = {}, -- 覆盖特定颜色
        -- highlights = {}, -- 覆盖特定高亮组
        options = {
          bold = true, -- 使用粗体
          italic = true, -- 使用斜体
          underline = true, -- 使用下划线
          undercurl = true, -- 使用波浪线
          cursorline = true, -- 高亮当前行
          transparency = false, -- 使用背景透明度
        },
      })
    end,
  },
  -- 禁用默认主题
  {
    "LazyVim/LazyVim",
    opts = {
      colorscheme = "onedark",
    },
  },
}

