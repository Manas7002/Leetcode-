import os
import re

def count_difficulties():
    easy, medium, hard = 0, 0, 0
    for root, dirs, files in os.walk("."):
        if ".github" in root or ".git" in root:
            continue
        if "README.md" in files and root != ".":
            readme_path = os.path.join(root, "README.md")
            try:
                with open(readme_path, "r", encoding="utf-8") as f:
                    content = f.read()
                    if re.search(r"\bEasy\b", content, re.IGNORECASE):
                        easy += 1
                    elif re.search(r"\bMedium\b", content, re.IGNORECASE):
                        medium += 1
                    elif re.search(r"\bHard\b", content, re.IGNORECASE):
                        hard += 1
            except Exception:
                pass
    return easy, medium, hard

def update_readme(easy, medium, hard):
    total = easy + medium + hard
    stats_markdown = f"""### 📊 LeetCode Progress Dashboard

| Difficulty | Solved Count |
| :--- | :--- |
| 🟢 **Easy** | {easy} |
| 🟡 **Medium** | {medium} |
| 🔴 **Hard** | {hard} |
| 🔢 **Total** | **{total}** |

_Last Updated automatically via GitHub Actions_
"""

    readme_path = "README.md"
    
    if os.path.exists(readme_path):
        with open(readme_path, "r", encoding="utf-8") as f:
            content = f.read()
    else:
        content = ""

    # 🔥 THE SELF-HEALING FIX: Completely wipe out ALL existing stats blocks (duplicates included)
    content = re.sub(r".*?", "", content, flags=re.DOTALL)
    
    # Also clear out any loose tables that lost their comment tags
    content = re.sub(r"### 📊 LeetCode Progress Dashboard.*?(?=\n\n|\Z)", "", content, flags=re.DOTALL)

    # Append exactly ONE clean block at the very end of the file
    new_content = content.strip() + "\n\n" + stats_markdown
    new_content = new_content.strip()

    with open(readme_path, "w", encoding="utf-8", newline="\n") as f:
        f.write(new_content)

if __name__ == "__main__":
    e, m, h = count_difficulties()
    update_readme(e, m, h)