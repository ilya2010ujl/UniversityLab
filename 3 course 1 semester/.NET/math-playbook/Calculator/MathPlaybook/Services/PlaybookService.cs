using System;
using System.Collections.Generic;
using System.IO;
using Calculator;
using ClassLibrary1;
using ClassLibrary1.Entity;

namespace MathPlaybook.Services
{
    public class PlaybookService
    {
        private readonly DBService _service;
        private readonly IContext _context;


        public PlaybookService(DBService service)
        {
            _service = service;
            _context = new Context();
        }

        public List<Block> GetPlayboookBlocks(int playbookId)
        {
            return _service.GetBlockByPlaybookId(playbookId);
        }

        public Block GetBlock(int blockId)
        {
            return _service.GetBlockById(blockId);
        }

        public void RemoveBlock(int blockId)
        {
            _service.RemoveBlock(blockId);
        }

        public void SwapBlocks(int i, int j)
        {
            _service.SwapBlock(i, j);
        }


        public void AddPlaybook(Playbook playbook)
        {
            _service.AddPlaybook(playbook);
        }

        public void AddBlock(Block block)
        {
            if (!block.Expression.Contains(";"))
            {
                try
                {
                    Calculator.Parser.Parse(block.Expression).Eval(_context);
                }
                catch (Exception e)
                {
                    Console.WriteLine("Block wasn't added");
                    return;
                }
            }

            _service.AddBlock(block);
        }

        public double CalculateBlock(int blockId)
        {
            var block = _service.GetBlockById(blockId);
            return Calculator.Parser.Parse(block.Expression).Eval(_context);
        }

        public void RemovePlaybook(int id)
        {
            var blocks = _service.GetBlockByPlaybookId(id);
            foreach (var block in blocks)
            {
                _service.RemoveBlock(block.Id);
            }

            _service.RemovePlaybook(id);
        }

        public BlockModel CalculatePlaybook(int playbookId)
        {
            var blocks = _service.GetBlockByPlaybookId(playbookId);
            var blockValues = new Dictionary<int, double>();
            string resultExpression = "";
            foreach (var block in blocks)
            {
                //So only blocks with ; calculated 
                if (block.Expression.Contains(";"))
                {
                    resultExpression +=
                        block.Expression.Substring(0, block.Expression.IndexOf(";", StringComparison.Ordinal));
                }
                else
                {
                    try
                    {
                        blockValues.Add(block.Id, Calculator.Parser.Parse(block.Expression).Eval(_context));
                    }
                    catch (Exception e)
                    {
                        Console.WriteLine("Block cant be calculated:" + block);
                    }
                }
            }

            try
            {
                if (resultExpression != "")
                {
                    var res = Calculator.Parser.Parse(resultExpression).Eval(_context);
                    blockValues.Add(-1, res);
                }
                return new BlockModel(blocks, blockValues);
            }
            catch (Exception e)
            {
                throw new InvalidDataException(e.Message);
            }
        }

        public List<Playbook> GetAllPlaybooks()
        {
            return _service.GetPlaybooks();
        }
    }
}