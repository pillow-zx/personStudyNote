return {
  {
    "neovim/nvim-lspconfig",
    opts = {
      servers = {
        -- 添加 Verilog LSP 配置
        verible = {}, -- 或者使用其他 Verilog LSP 服务器
      },
    },
  }
}
