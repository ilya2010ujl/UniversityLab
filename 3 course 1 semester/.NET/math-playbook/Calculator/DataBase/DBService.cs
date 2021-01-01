using System;
using System.Collections.Generic;
using System.Linq;
using ClassLibrary1.Entity;

namespace ClassLibrary1
{
    public class DBService
    {
        private readonly PlaybookContext _playbookContext;

        public DBService(PlaybookContext playbookContext)
        {
            _playbookContext = playbookContext;
        }

        public Block GetBlockById(int id)
        {
            return _playbookContext.Blocks.FirstOrDefault(b => b.Id == id);
        }

        public List<Playbook> GetPlaybooks()
        {
            return _playbookContext.Playbooks.ToList();
        }

        public List<Block> GetBlockByPlaybookId(int id)
        {
            return _playbookContext.Blocks.Where(b => b.PlaybookId == id).OrderBy(b => b.Id).ToList();
        }

        public void RemovePlaybook(int id)
        {
            var playbookToRemove = _playbookContext.Playbooks.SingleOrDefault(p => p.Id == id);
            _playbookContext.Playbooks.Remove(playbookToRemove);
            _playbookContext.SaveChanges();
        }

        public void SwapBlock(int i, int j)
        {
            var blockI = GetBlockById(i);
            var blockJ = GetBlockById(j);
            var newBlockJ = new Block();
            var newBlockI = new Block();

            newBlockJ.Expression = blockI.Expression;
            newBlockJ.PlaybookId = blockI.PlaybookId;
            newBlockJ.Id = j;

            newBlockI.Expression = blockJ.Expression;
            newBlockI.PlaybookId = blockJ.PlaybookId;
            newBlockI.Id = i;

            _playbookContext.Blocks.Remove(blockI);
            _playbookContext.Blocks.Remove(blockJ);
            _playbookContext.SaveChanges();

            AddBlock(newBlockJ);
            AddBlock(newBlockI);
        }

        public void RemoveBlock(int id)
        {
            var blockToRemove = GetBlockById(id);
            _playbookContext.Blocks.Remove(blockToRemove);
            _playbookContext.SaveChanges();
        }

        public void AddBlock(Block block)
        {
            _playbookContext.Blocks.Add(block);
            _playbookContext.SaveChanges();
        }

        public void AddPlaybook(Playbook block)
        {
            _playbookContext.Playbooks.Add(block);
            _playbookContext.SaveChanges();
        }
    }
}