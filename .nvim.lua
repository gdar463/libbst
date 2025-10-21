vim.api.nvim_create_autocmd("LspAttach", {
	callback = function()
		vim.diagnostic.config({ virtual_text = false })
	end,
})
