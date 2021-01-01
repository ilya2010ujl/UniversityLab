using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Calculator;
using ClassLibrary1.Entity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using MathPlaybook.Models;
using MathPlaybook.Services;

namespace MathPlaybook.Controllers
{
    public class MathController : Controller
    {
        private readonly ILogger<MathController> _logger;
        private readonly PlaybookService _service;

        public MathController(ILogger<MathController> logger, PlaybookService service)
        {
            _logger = logger;
            _service = service;
        }

        [HttpGet("/")]
        public IActionResult Index()
        {
            var playbooks = _service.GetAllPlaybooks();
            return View(playbooks);
        }

        [HttpGet("/playbook")]
        public IActionResult Playbook(int id)
        {
            var blocks = _service.GetPlayboookBlocks(id);
            var model = new BlockModel(blocks);
            return View(model);
        }

        [HttpPost("/addPlaybook")]
        public IActionResult AddPlaybook(Playbook playbook)
        {
            _service.AddPlaybook(playbook);
            return Redirect("/");
        }


        [HttpGet("/calculatePlaybook")]
        public IActionResult CalculateAll(int id)
        {
            var model = _service.CalculatePlaybook(id);
            return View("Playbook", model);
        }

        [HttpGet("/remove")]
        public IActionResult Remove(int blockId)
        {
            var block = _service.GetBlock(blockId);
            _service.RemoveBlock(blockId);
            return Redirect($"/playbook?id={block.PlaybookId}");
        }

        [HttpGet("/swap")]
        public IActionResult MoveUp(int i, int j)
        {
            _service.SwapBlocks(i, j);
            var block = _service.GetBlock(i);
            return Redirect($"/playbook?id={block.PlaybookId}");
        }


        [HttpPost("/addBlock")]
        public IActionResult AddPlaybook(Block block)
        {
            _service.AddBlock(block);
            return Redirect($"/playbook?id={block.PlaybookId}");
        }

        [HttpGet("removePlaybook")]
        public IActionResult RemovePlaybook(int id)
        {
            _service.RemovePlaybook(id);
            return Redirect("/");
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel {RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier});
        }
    }
}