= AIとコラボして人気絵師になる

//image[StableDiffusion_fig1][Stable Diffusion によるイラスト生成例(筆者とのコラボで制作)]{
//}


== 「例のAIが描いた絵です、プロンプトは秘密です！」
「例のAIが描いた絵です、プロンプトは秘密です！」って人間の絵師が自分で描いた絵をイラスト投稿サイトで売り始める未来までは見えた…って、いうツイート@<fn>{tweet0824}が軽くバズってしまったその後の話になります。

前提として、私自身、人間が描く行為は大好きです。
自身も学生時代はマンガを描いてました。
過去形でなく、映像を作るうえではスケッチやキャラクターデザイン、指示書や発明の図など、マンガは業務でも描きます。
そう人間の手で描くイラストレーションを愛しています。
「AIで描けるなら人間は絵を描かなくていい」ってことはないと思いたい。人類バンザイ！

しかしそれはそれとして、業務でのスケッチは心の状態の向き不向きに関係なくサッサと描いてしまいたいですし、
それに「有名・神絵師」ならぬ「有名AI」であったとしても「クオリティの高い絵なら見てみたい」のではないでしょうか？
少なくとも私は観たいと思います。

そして(あわよくば)人間の絵師が「私は有名AIです」といってイラスト投稿サイトで有名になるようなこともできるんじゃないか？という未来です。
もう来月ぐらいには一般的になるんじゃないかなと。
そこまで行くと人類はまた新たなステージに立てると思いますので、本稿では「AIとコラボして人気絵師になる」、そのための技術開発を目標に調査研究してみたいと思います。



== 人工知能で絵を描くための前提知識と用語

さて本題に入ります。「最近は人工知能で絵を描くことができます」というこの1行のために、何本かの論文を読む必要があります。
オッサンが鉛筆を削ってデッサンをゼロから学ぶよりははるかに楽なので付き合ってください。

本稿では「Stable Diffusion を使っていい感じの萌え絵の素材を描かせるためのプロンプト（呪文）」を理解する、という技術の根幹と使い手としての入門を同時に達成するために、
数式を一切使わずに、思い通りの結果を得るために必要な研究を解説していきたいと思います。
その過程で DALL-E や MidJourney 、Stable Diffusion の背景に使われている技術が面白いな、このスピード感はついていかないと置いていかれるな…そう思えればそれでOKです。

=== 人工知能で絵を描く研究開発の歴史と背景
「人工知能で絵を描く」と一言で表現しても、いろいろな要素が出てきました。古くは画像理解や、GA（Generative Algorithm；創発的アルゴリズム、もしくはGenetic Algorithm；遺伝的アルゴリズム）、さらに画像生成分野ではNPR（Non-Photorealistic Rendering；非写実的な画像生成）、さらにレタッチ分野では Photoshop などを長年開発している Adobe社がとても強いです。Adobe には Adobe Research という研究グループがあります。彼らは画像を直感的な作業で改善するというシンプルな出発点から、写真のフィルタリング技術、背景の除去などを長年開発してきました。最近では、動画の音声を文字起こししてくれたり、簡単なレイアウトを描くだけで神々しい背景画像を作り出してくれたり…となかなか便利そうな技術が国際会議やカンファレンスなどでのデモで発表されています。

一方で、Adobe のような企業は製品を売って利益を得る企業です。独占的なAIの開発はある目的にとっては良いかもしれませんが、オープンではなく、多様な用途には向いていませんし、ブラックボックス化する技術に対して「人間たちが勝手に恐怖を抱いてしまい、逆に普及しない」というジレンマもあります。
そんな背景もあって、2015年にテスラ社のイーロン・マスクを始めとする実業家・投資家によって設立されたオープンな人工知能研究機関が「OpenAI」です。
OpenAI は、人工知能を研究する非営利団体で、人類全体に「害をもたらすよりは、有益性があるやりかた」で、オープンソースと親和性の高い人工知能を注意深く推進することを目的としています。
これまで GPT (Generative Pretrained Transformer) のような自然言語処理、言語のメタ学習が可能なアルゴリズムを発表していましたが、最近は DALL-E という「文字列から（意味を解釈して）画像を生成するAI」を発表しています。
文字列から画像を生成するだけであれば、その他にもいくつかの人工知能や類似のシステムは存在しましたが、その改善版「DALL·E 2」においては、自然言語による記述からリアルな画像やアートを作成できる新しいAIシステムとなりました。

そして本稿を書いている2022年8月末の時点で明言しておきたいことは、DALL-E の登場以前は、「コンピュータが描いた絵」に人々は驚きこそすれど、人気になったり、親しみを得たり、もしくはそこに熱狂してお金を投じたりといった対象ではなかったかもしれない、という点を指摘しておきます。

たとえば2021年ごろに熱狂的なブームとなった NFT（Non-Fungible Token）アートは、「代替不可能なトークン」つまり、偽造や改ざんが難しいブロックチェーン技術によって、ネットワーク上の画商やその市場を開拓しました。100～1000といった有限なセットで発売されるため、「有名な絵師さんによる、限定性」が商品の価値を高める要素になります。
一方では大量に記号的なアートを生成する中で「私はこれが気に入った」という自己主張やコミュニケーションとして使われて行きます。
つまり、有限な組み合わせによって生成されるアバター市場や、GAによって生成されるコンピュータによる画像生成、そしてその趣味嗜好（preferred；好ましい）モデルを獲得する事には、メタな技術としての強みが生まれます。

=== CLIP 潜在性を用いた階層的テキスト条件付き画像生成法
さてここでは、2022年4月にOpenAIの Aditya Ramesh らによって書かれた「DALL·E 2」についての論文「Hierarchical Text-Conditional Image Generation with CLIP Latents（筆者による邦題；CLIP 潜在性を用いた階層的テキスト条件付き画像生成法）」(https://arxiv.org/abs/2204.06125)を平易な日本語で関連用語とともに解説していきたいと思います。
私自身は知能システム科学で博士を取得したのですが、この分野は査読などの経験はないのでシロウトです。紹介するのは最新の研究なので間違っていることもあるかもしれないです。

==== Diffusion モデルと関連する専門用語

解説を通して専門用語がいくつか出てきます。
このあとの急速な進化が予感される「AIで絵を描く技術」、特に Stable Diffusion で覚えておきたい用語は「Diffusionモデル」、そしてその背景にある「CLIP」と、「GLIDE」とそれらを支える技術でしょうか。
一つ一つ理解しやすいステップで、簡単な言葉で説明していきたいと思います。

==== CLIP : 文字と画像をつなぐモデル

まずOpenAIの先行研究として CLIP (Connecting Text and Images；テキスト画像接続) という手法があります。
「CLIP」は「WebImageText」という画像とそれを説明するフリーテキストのペアでできた4億のテキストと画像のペアを対象学習（Contrastive Learning/コントラスト学習）で学習させた自然言語教師型画像分類モデルです。
「画像とテキストの関係、類似度を測ることができる巨大な表」とイメージするとよいでしょう。
CLIPもunCLIPなど複数の改善バージョンが存在しています。

多様なタスクに対して「ゼロショット」、つまり何度もショットを取らない、タスク特有の学習内で、事前学習データだけで学習したモデルを直接タスクに転用することができるという特徴があります。

CLIP のような既存手法では「セマンティクス」（≒意味、この場合は画像の領域に描かれた意味）と、「スタイル」の両方を捉えた頑健な画像表現を学習することできます。
この「意味」と「表現」の2つを画像生成に活用することを考えて、「キャプション」（注釈として与える文字列）を指定してCLIP画像への埋め込みを生成する「事前のモデル」（prior；事前分布）と、画像埋め込み(embed)を条件として画像を生成する「デコーダ」の2段階によるモデルを提案しています。

つまり画像の表現スタイルを明示的に文字列で指定すれば、フォトリアリズムな表現とキャプションで指定された「意味の類似性における差を最小限に抑えつつ、画像の多様性を向上させられるという」手法です。
さらに、CLIP に結合されている埋め込まれた意味空間は、ゼロショットで（つまり事前の知識やゴールの設定なく）言語誘導的な画像操作を可能にします。デコーダには後述の「拡散モデル（Diffusion Model）」を用います。論文によると、事前分布には自己回帰モデルと拡散モデルの両方を用いて実験し、後者の方が計算効率が良く、より高品質なサンプルを生成できると報告しています。

このあとに続く研究でも CLIP の手法 が使われています。
そして、当然なのですが、この CLIP で学習したものが、このあとの結果に大きな影響を及ぼします。

==== DDPM: ノイズ除去拡散確率モデル
「Diffusionモデル」は「Stable Diffusion」の「Diffusion」の語源にもなっている「拡散」のことです。
画像生成手法の一種で、DALL-E2では GLIDE という Diffusionモデルによる Text-to-Image生成モデルが使われています。
フルネームでは「ノイズ除去拡散確率モデル（Denoising Diffusion Probabilistic Models）」というモデルで、DDPM と呼ばれます。

==== 逆マルコフ過程と超解像技術（SR）
DDPM を理解する上では、2015年ぐらいから研究されている超解像（Super Resolution; SR）の技術を理解せねばなりません。
まず画像に微小なノイズを足していく過程を考えます。これは「マルコフ過程」として表現できます。
マルコフ過程とは、未来の挙動が現在の値だけで決定され、過去の挙動と無関係であるという性質を持つ確率過程です。
基本情報技術者試験に出そうな問題で例えると、
「天気は1日前の天気にのみ依存するマルコフ過程である」という例題があります。
晴れの翌日は40％で晴れ、40％で曇り、20％で雨、といった確率で変化し、曇り→雨、雨→曇りなど全てのとりうる状態が確率で表現できて、前日より前の天気には依存しないとするとします。
「雨の日の2日後が晴れになる確率は？」という一見複雑な問題に、マルコフ過程は「晴れになる確率」を単純に足し合わせるだけで回答を出すことができます（単純マルコフ過程）。

ここで「各ステップごとに画像データにノイズを加えていく過程」を考えます。
これは「破損プロセス」と表現できます。とある現在の画像に対してノイズを加えていくのであり、それぞれのステップは過去のすべての行為とは無関係といえます。
DDPMでは、このような思い切った考えで、破損プロセスの逆過程、つまりノイズから実データを復元するようにモデルを学習させていきます。
ノイズはガウス分布という一般的な発生の確率に沿わせます（違うノイズの与え方もあります）。
そして、その逆工程もマルコフ過程として表現できるので、この逆の工程を学習させることで、ガウス分布ノイズの塊から画像を復元できる学習を獲得できる…という魔法のような手法です。

論文としてはSR3と呼ばれる手法の「Image Super-Resolution via Iterative Refinement（筆者訳；反復精製による画像の超解像化）」（https://arxiv.org/abs/2104.07636）を引用しておきます。

=== 超解像技術を用いたノイズ除去拡散確率モデル条件付き画像生成
DDPMとSRはちょうど絵を描く工程に例えると、真っ白な紙にポスターカラーで絵を描いていくような工程があったとして、その完成図から工程を逆にたどるような条件で学習を行えば、（紙が白かろうが何だろうか）ノイズの塊から目的の絵を描くことができる、ということになります。

「猫を描こう」と思ったら、完全なガウスノイズが乗った猫→ノイズを減らした猫→ノイズがない猫の画像を用意して、その逆工程、つまりデノイズをピクセル単位で獲得していきます。
ガウスノイズは近隣のピクセルとは異なる、色が派手な変化を起こしますので、この理想的な分散を持ったノイズを除去できる学習は、目的の絵を生成できるはず、ということですよね（何故なのか？はここでは一旦置いておきます）。
ただし「白い紙」ではなくシード値から生成したガウスノイズから生成するので、乱数の要素があります（シードが同じであれば再現性はあります）。

この「猫」を画像ではなく、猫のミーム、つまり猫を表現するようなWebから拾ってきた画像で学習させたものが「超解像技術」＋「ノイズ除去拡散確率モデル」＋「条件付き画像生成」となります。
確率的ノイズ除去処理によって超解像、つまり本来なかった倍率まで解像度を上げていく……という技術ですが、特に顔や自然画像に対して高い性能を発揮します。


=== GLIDE：テキストガイドによる拡散モデルを使った写実画像生成

さて、超解像技術の場合は「もともと描かれていた画像に対して、解像度を上げていく」という条件付けですが、この潜在変数を CLIPの潜在性 (CLIP Latents)に注目し、画像と言語の関係に埋め込まれた意味（セマンティック）にしたものが GLIDE です。
OpenAIの「DALL·E」から約1年、進化モデルは「テキストガイドによる拡散モデルを使った写実画像生成・編集を目指したアルゴリズム『GLIDE』」として発表されました@<fn>{GLIDE}@<fn>{GLIDE-Paper}。
拡散モデルによってノイズを徐々に除去する際に、CLIPの潜在性を埋め込んで分類器の出力誘導を行い、目的の方向に生成を「誘導する」ことができます。

35億パラメータで Diffusion モデルを学習し、もともとの意味としての画像は 64x64 ピクセルのジグソーパズルのようなピースでのセマンティックで作ります。
このセマンティックは「デコードするといい感じの画像を生成する潜在変数」と理解することができます。
このままでは 64x64 ピクセルですが、ここに「超解像技術」を組み合わせることで、最終的にフォトリアルな画像として、256x256ピクセルで画像が生成できます。
がんばれば512x512など画像サイズを上げていくことができますが、さらに大きなメモリ空間が必要になります。
また1ピクセルづつ、1工程づつデノイズを行っていくので、非常に効率が悪い処理をではあります。

なお、レイアウト上、複雑になるとうまく生成できない問題がありますが、生成→編集についても提案されています。
領域を指定することで人間がさらに補っていくことで完成させるという手法も並列して存在します（過度な脱線を避けるため、本稿ではワンショットで、領域指定をしない手法を中心に紹介していきます）。


=== DALL·E 2：CLIPと拡散モデルを組み合わせた2段階モデル
さて、やっと「DALL·E 2」に辿り着きました。
DALL·E 2はCLIPとGLIDEを組み合わせた2段階モデルで論文内では「unCLIP」と呼ばれています。

「unCLIP」はテキストから画像の埋め込みを得る「事前分布 (prior)」と、
CLIPの画像埋め込みとテキストから画像自体を生成する「デコーダ (decoder)」の2段階によって構成されます。

自然言語による記述文と、「デコーダ」は、CLIP 画像埋め込みから生成します。
画像を説明する説明文が言語モデルを介して「embedded特徴」に変換されます。
学習と生成は以前と同じように進行しますが、ノイズ除去の追加入力としてヒントを提供するテキスト入力が入ります。
画像を受け取ってembedded特徴を生成するので、「CLIP を反転しているものだ」と考えればよいかもしれません（なので unCLIP と呼んでいるのかも）。



== MidJourney を使ってみる

さて技術は使ってみなければその本質はわかりません。
まずは 「DALL·E 2」と「Stable Diffusion」の間に生まれた「MidJounery」を使って試してみました。

 * 「MidJounery」 https://www.midjourney.com/home/

Discordをインターフェースとしており、25枚は無料で生成することができます。会員登録していれば商用利用も可能とのこと。
ちょうど仕事でコンセプト画を描かなくてはならないので、例として「@<tt>{high school girl in metaverse}（メタバースにおける高校生の少女）」などをプロンプトにしています。


//image[StableDiffusion_MidJourney][(左)@<tt>{"high school girl in metaverse"}／(右)超解像化された結果]{
//}

細かい造作を入れていきたいので、「@<code>{REALITY manga style smiling avatar female with wings and cat ears}（REALITY, マンガ風, 笑顔の, アバター女性, 羽と猫耳付き）」で探索してみます。

そもそも ``REALITY'' が何のことなのか、知っているのかどうか？でいうと、そもそもこれは判定が難しいワードですね。
結果としては雰囲気はないこともない（実験したのは2022/8/4ごろです、今後変わる可能性もあります）。

いろいろ試してみるとVTuberについての知識はありそうなので、今度はスタイルの指定に使ってみます「@<tt>{vtuber style female avatar singing}（VTuber風, 女性アバター, 歌ってる）」としてみます。

//image[StableDiffusion_MidJourney2][(左)"REALITYマンガ風微笑みアバター 女性 翼と猫耳付き／(右)VTuber風女性アバター 歌ってる]{
//}


以上のように「有効そうな単語」を探り、でき上った画像から良さそうなものを選んで、それをシードにしてさらに画像を探求していく…という工程をDiscordのチャットを使って超高速に進めていきます。


=== MidJourney は仕事につかえるかどうか

「MidJourney は仕事につかえるかどうか？」という視点で判定してみます。
まずは、形容詞で「赤い髪」とか「青い髪」といった指定ができる要素であればよいのですが、
裏側で動いているアルゴリズムやモデルが謎すぎます。
おそらくCLIPが動いており、word2vecのようなワードベクトルで指定することである程度の類似度やベクトルを指定できる可能性があるので、学習している対象が日本のアニメやマンガではなく、欧米文化の映画やスーパーレアリズムが多く、インパクトのある背景画は生成できますが、安定した萌え絵には使いづらい。
例えば「日本」に関係する画像はいつも富士山とか五重塔のような建造物が現れてしまいます。
また人物に関しては、いつも出てくる人物の雰囲気がいつも同じなので、いくつか画像を生成すると『ああ。MidJourneyだね』という感想を抱いてしまうと思います。


今後モデルの改善が期待されますが、改善されることで結果も変わってしまう可能性があります。安定した結果を出すには難しい。
一方では、超解像技術のおかげもあって、ディテールについては非常に印象深い仕上がりをするので、
「企画者としてのコンセプト画像の検索」という使い道ではいけるように感じました。


=== MidJounery が切り拓いた「AI画像生成というエンタメ」

MidJounery は仕事には使えないかもですが、DiscordをインターフェースとしたAI画像生成体験は、
「MidJourneyはエンタメ体験として成立している」という印象を得ました。
GPUや Discordを使ったUXとしてのターンアラウンドの処理のテンポも重要で、「お金払う価値はあるかも」と思わせる体感があります。
何より周りの人たちが一生懸命画像を生成しているのを見るのは、なんだか熱狂を感じます。

ところで「お絵描きAI」は人類にとって何者なのでしょうか。
「思い通りの絵を描かせたい」という人類、つまり「攻略したいゲーマー(人類)」にとって、遊び相手になってくれる相手でしょうか。

少なくとも、デジタルイラストレーションの世界で勝ち負けで勝負をする相手としてみると、「勝敗をつけるよう場所で戦ってはいけない相手」ではない感じがします。
「そもそもアートに勝敗はありませんよね」という立場を守るのが人類にとって幸せな選択になるでしょう。

DALL-2Eでは修正して「一緒に絵を描く」という貢献が求められましたが、MidJourneyではAI神絵師に呪文を唱えるゲーム的な体感があります。
ものの数秒で生成されてDiscordでメンションされるのですが、これは反応速度が高いGPUが搭載された演算が必要そうな感じがしますし、
その反応のテンポのよさに、コストを払ってゲーム的に楽しみたい人もいそうです。また攻略性だけでなく、癒しにもなります。

例えば「今まで見たことがない癒し猫画像で癒されたい…」といった需要があると思いますが、現実空間で撮影された画像には限界があります。
「どこか遠い宇宙を背景にしたファンタジーイラストで、癒される猫の画像を見たい…」という要求に対して、MidJourney が生成する画風やモチーフはフォトリアルやスーパーリアリズムとしては印象的です。


=== プロンプトエンジニアリングの必要性

MidJourneyは他の人が打ち込んでいるプロンプトが見えているので、えっちな画像をひたすら作り出そうと頑張っている人もいます。
それがプロンプトの改善の参考になったりもして、何というか「何でも描いてくれる絵師さんにひたすら性癖をこすりつけているキモい空間」でもあります（そもそも利用規約違反かもしれません）。
一方では、目的の絵を生成させるプロンプトを見つけ出すプロンプトエンジニアリングの必要性を感じます。

そういえば英語の prompt はラテン語の promptus（前へ取り出した）という語で、語源としてはラテン語 promo（前へ取り出す）⇒ ラテン語 pro-（～の前へ）＋emo（取る）が語源。つまり即座に emptus(手に入れる)という意味で、人類が神様にこの神絵師にうまく絵を描いてもらえる@<ruby>{詔, ミコトノリ}ではあるけれど、その神主になって即座に入手する技術も「誰にでもできる技術」ではなくなっていくことが何となく感じられます。

このあとの「Stable Diffusion」では、内部のモデル理解を含めて、AIとよりよいコラボができる神絵師プロンプトについても探求していきます。

== Stable Diffusion：潜在拡散モデル

Stable Diffusion は  ドイツの大学系研究所「CompVis」（https://github.com/CompVis）、 Stability AI（https://stability.ai/） 、LAION（https://laion.ai/）の研究者やエンジニアによって作成されたテキストから画像への潜在拡散（latent diffusion）モデルです。

このモデルは 、frozen CLIP ViT-L/14 テキストエンコーダを使用し、LAIONによる美的に「美しい」と推定される審美的なデータセット「LAION-Aesthetics V1」@<fn>{LAION}で学習し、
テキストプロンプトでモデルの条件付けを行います。
#@# 860MのUNetと123Mのテキストエンコーダを持つこのモデルは、
比較的軽量で、コンシューマー向けGPU、10GB以下のVRAMで動作し、512×512ピクセルの画像を数秒で生成します。

Stable Diffusion は 64x64 のガウスノイズの潜在変数シード(Latent Seed)を与えてノイズ除去超解像化を行う過程に、
ユーザの与えたプロンプトを CLIP を通して生成したテキスト埋め込み(77x768次元)の潜在変数に沿うように誘導するという手法を使っています。

簡単に表現すると、人間が言語で与えた意味（セマンティック）を77x768次元の単語→ベクトルに変換する辞書に渡して、その辞書に近いベクトルに沿わせながらノイズ→512x512画像にノイズ除去しながら超解像化しているということになります。

なお与えた単語の意味をベクトルで保有していますのでWord2Vecのように単語間の類似や加算減算なども可能なようです（言語で指定することは難しいが）。


論文@<fn>{HR}や、利用のためのライセンスなどは後ほど Google Colaboratory での利用において解説します。

//footnote[HR][High-Resolution Image Synthesis with Latent Diffusion Models, https://arxiv.org/abs/2112.10752]

#@# ジェネレーティブAI開発者のKatherine Crowson氏による条件付き拡散モデル（conditional diffusion models）、
#@# Open AIによるDall-E 2、Google BrainによるImagen、その他多くの洞察と組み合わせて構築されたもので、任意のテキスト入力から写真のようにリアルまたはアーティスティックな画像を生成することができます。
#@# 画像の一部を塗りつぶしてテキスト入力すると、その箇所だけテキスト通りに描き加えることができます。
#@# しかも、描き加えたその箇所は、周囲の文脈のスタイルや照明に応じた影や反射を含み、周囲と調和した画像が合成されて生成されます。

=== MidJourney と Stable Diffusion の根本的な違いと今後

MidJourneyはブラックボックスなので、技術的に根本的な違いがあるかどうかは明言できません。
MidJourneyもその後、内部で Stable Diffusion を取り込んだらしく、プロンプトに「--beta」を使うだけでカワイイ対応が可能になったそうです。

しかしテキストから画像を生成できるモデル、しかも MidJourney のような商用利用ベースのブラックボックスではなく、
ソースコードも学習モデルも無料で利用できる、しかもそのモデルが非常に高品質な結果を生み出せる、というのが Stable Diffusion が有名になったポイントですが、
ここまでの簡単な解説で、超解像技術 → 拡散モデル → GLIDE → DALL·E 2 → MidJourney → Stable Diffusionという、地道な技術の進歩が超短期間でおきていること自体が脅威でもあります。

そして、数日でトレンドを塗り替えられてしまった MidJourney。
この背景にあるのは「拡散モデル」の発展であり、学術系研究者グループや、AIスタートアップが知見と結果を出し合いながら、あっという間に私企業によるサービスを塗り替えていきました。
そしてこの技術は画像生成だけではなく、言語や音声など他のドメインでのデノイズや創作の質向上が期待できそうです。
MidJourneyのファウンダーはLEAPのファウンダーでもあるので、きっと大きな変革をしてくれると思います。
そもそも Stable Diffusion に人気の座を奪われた数日後には Stable Diffusion を取り込んでいました。


== Stable Diffusionで絵を描くテクニック

さて Stable Diffusionを使って絵を描いてみます。

ここから先はちょっと真面目に「良い生成結果」と「人気絵師になる工程」を残していく意味もあって（また、紙面ではあまりに量が多いので）、pixivさんのほうに画像を置いてあります。

使い手の進化の過程がわかるので、まずはこちらをフォローしていただくのが良いかなと思います。

 * 【筆者の実験用pixiv】 https://www.pixiv.net/users/1355931/illustrations

//image[StableDiffusion_PixivShirai][筆者の実験用Pixiv(短縮リンク) ivtv.page.link/PixivShirai]{
//}

お手元のスマホでこちらのQRコードを使って見ていただくのもよいかと思います。

=== 注意事項

以下のプロンプトについては解説目的で共有しますが、一部伏せさせていただきます。
特に商標に関わるキーワードと商品性が高いキーワードがあります。
そして「萌え絵」になると、性癖が露になるキーワードが多くなりますので、あえて日本語で表現するときには緩めに翻訳しています。
もしどうしても知りたい、という方は pixiv上からコミュニケーションしていただくか、Twitter@o_ob にてお問い合わせください（呪文を忘れてしまっていたらごめんなさい）。


== Stable Diffusion - Dream Studio による探求

皆さんお待ちかね、Stable Diffusionによる作例です。自分は Dream Studio LiteというUIサービスを使っています。

基本はプロンプトを入力して「Dream」ボタンを押すだけです。

 * https://beta.dreamstudio.ai/

スマホでも使いやすいWebインターフェースになっているのが特徴です。
無料枠がありますが、すぐに使い切ってしまうかもしれません。メンバーシップで10ポンドを支払うことで 1,000 generations（クレジット） を生成することができます。
「基本の設定で1000回はリクエストできる」ということですが、けっこう夢中になるとあっという間に使い切ってしまいます。

画面の解説をします。

//image[StableDiffusion_DreamStudioUI][Dream Studio のUI。プロンプトを入力して「Dream」ボタンを押すだけ]{
//}


 * Width, Height：画像の解像度です。デフォルトは 512x512 pixels。最大は 1024x1024 pixels。クレジットを消費するので必要がないときは小さいほうが良いです。また小さくしておくほうが高速動作します。
 * Cfg Scale：画像がどの程度プロンプトと同じになるかを調整します。値を大きくすると画像はプロンプトに近くなります。
 * Steps：画像の生成過程での「Diffusion」に何回のステップを行うか？デフォルトでは 50 Steps です。10 Steps で 0.2 credits, 最大の 150 Stepsで3.0 credits を消費します。
 * Number of Images：これはめんどくさがりには良いですね。サイコロを同時にたくさん振ることができます。最大9件の画像を生成することができます。クレジット消費量の表示は変わりませんが、減るスピードがあっという間になりますのでご注意ください。
 * Sampler：k_lms(デフォルト), ddim, plms, k_euler, k_euler_oncestral, k_heun, k_dpm_2, k_dpm_2_oncestral で、Diffusion のサンプリング方式を指定します。
 * Seed：画像生成のための乱数シード、おそらく最初のガウスノイズの生成のために使われると推測します。つまり、このシード値を保存しておけば、そこそこに近い結果を検討することができるはずです。
 
お値段的には ｛画像サイズ｝x ｛Steps｝の掛け算になっているようで、最大サイズの 1024x1024 pixels で Steps = ｛10, 25, 50, 75, 100, 150｝としたときに、消費クレジットはそれぞれ｛1.9, 4.7 , 14.1, 18.8, 28.2 ｝となっています。1000 クレジットが 10ポンドなので、1617.8 円。1クレジットあたり16.178円（2022/8/31のレート）。デフォルトだと17円/生成。最大でも457円/生成、ということになります。


=== プロンプトエンジニアリングの基本（公式ガイドの参考訳）

 * 【公式ガイド】 https://beta.dreamstudio.ai/prompt-guide
 * 【著者： @Graverman 】https://twitter.com/dailystablediff

（以下参考訳です）
初心者がテキストから画像を生成するAIを使って、より良い画像生成するための簡単な公式を提案します。
これは Stable Diffusion でテストされましたが、十分なアートデータで訓練されていれば、どんなモデルでも使えるはずです。
このドキュメントを読み、これらの簡単なステップを適用した後、あなたは同じ労力でより良い画像を生成することができるようになります。

==== 1. 生のプロンプト
生のプロンプト(Raw Prompt) とは、例えば、生成したいものを記述する最もシンプルな方法です。
パンダ「@<tt>{Panda}」， 剣を持った戦士「@<tt>{A warrior with a sword}」，スケルトン「@<tt>{Skeleton}」……
これはプロンプトの基本的な構成要素です。ほとんどの初心者は、生のプロンプトだけを使うことから始めますが、これは通常間違いです。
このようにして生成された画像は、ランダムで無秩序になる傾向があるからです。以下は、私が以前のプロンプトを実行して生成した例です。

//image[StableDiffusion-prompt-guide-example][Dream Studio example]{
//}

見てわかるように、これらの画像は風景が不規則で、とても美的センスがあるとは思えません。ここで、次のポイントに移ります。

==== 2. スタイル
スタイルは、プロンプトの重要な要素です。AIは、指定されたスタイルがない場合、通常、関連する画像で最も多く目にしたものを選択します。
例えば、私が風景を生成した場合、おそらくリアルな画像や油絵のような画像を生成することでしょう。
スタイルは生のプロンプトの直後に画像に最も影響を与えるため、よく選ばれたスタイルと生のプロンプトを持つだけで十分な場合があります。

最も一般的に使用されるスタイルは…… 
リアリスティック「@<tt>{Realistic}」，
油絵「@<tt>{Oil painting}」，
鉛筆画「@<tt>{Pencil drawing}」，
コンセプトアート「@<tt>{Concept art}」，
これらのスタイルをどのように使うか、1つ1つ検証していきます。

リアルな画像の場合、そのスタイルには様々な方法があり、ほとんどが似たような画像に仕上がります。
ここでは、よく使われる写実的な画像にするためのテクニックを紹介します。

 1. ある写真＋生のプロンプト「a photo of+ raw prompt」
 2. フォトグラフ＋生のプロンプト「a photograph of + raw prompt」
 3. 生のプロンプト＋ハイパーリアリスティック「raw prompt, hyperrealistic」
 4. 生のプロンプト＋リアリスティック「raw prompt, realistic」

もちろん、これらを組み合わせることで、よりリアルな画像を得ることができます。
油絵を取得するには、プロンプトに「an oil painting of」を追加するだけです。
この場合、フレーム内の油絵が表示されることがありますが、これを修正するには、プロンプトを再実行するか、生プロンプト + 油絵「oil painting」を使用することができます。
鉛筆画を作成するには、生のプロンプトに「a pencil drawing of」を追加するか、生のプロンプト＋「pencil drawing」とするだけです。
風景画の場合も同様です。

筆者追記：ここにカメラの製品名やレンズの焦点距離を入れるというテクニックも見つかっています（例：photo by Canon EOS 5D 80mm）

==== 3. アーティスト

自分のスタイルをより具体的にしたり、イメージをより一貫したものにするために、プロンプトにアーティストの名前を使用することができます。
例えば、非常に抽象的なイメージにしたい場合は、「パブロ・ピカソ作」“made by Pablo Picasso” または単に ピカソ「Picasso」と付け加えるとよいでしょう。

以下に、さまざまなスタイルのアーティストのリストを掲載しますが、新しいアートを発見するクールな方法として、常にさまざまなアーティストを検索することをお勧めします。

 * ポートレート：John Singer Sargent, Edgar Degas, Paul Cézanne, Jan van Eyck
 * 油絵：Leonardo DaVinci, Vincent Van Gogh, Johannes Vermeer, Rembrandt
 * 鉛筆・ペン画：Albrecht Dürer, Leonardo da Vinci, Michelangelo, Jean-Auguste-Dominique Ingres
 * 風景画：Thomas Moran, Claude Monet, Alfred Bierstadt, Frederic Edwin Church

作家を混ぜることは、面白い作品を作ることにつながるので、大いに推奨されます。

==== 4. 仕上げ
この部分は、人によっては極端になり、この記事よりも長いプロンプトを作ることもあります。
仕上げ（Finishing touches）とは、プロンプトを自分の好きなように仕上げるために、最終的に追加するもののことです。
例えば、よりアーティスティックなイメージにしたい場合は、アートステーションで流行っている「trending on artstation」（www.artstation.com）を追加します。
よりリアルなライティングを追加したい場合は、「Unreal Engine」を追加します。何を加えてもいいのですが、以下に例を挙げます。

#@# 高精細「@<tt>{Highly detailed}」、シュールレアリズム「@<tt>{surrealism}」、アートステーションのトレンド「@<tt>{trending on art station}」、トライアド配色（色相環を使った3角配色のこと）「@<tt>{triadic color scheme}」、スムーズ「@<tt>{smooth}」、シャープフォーカス「@<tt>{sharp focus}」、マット「@<tt>{matte}」、エレガント「@<tt>{elegant}」、今まで見た中で最も美しい画像「@<tt>{the most beautiful image ever seen}」、イラスト「@<tt>{illustration}」、デジタルペイント「@<tt>{digital paint}」、暗い「@<tt>{dark}」、陰鬱「@<tt>{gloomy}」、「@<tt>{octane render}」（ Cinema4D や Blender に使われている Otoy社製の高品質レンダリングエンジン）、@<tt>{8K}、@<tt>{4K}、ウォッシュドカラー「@<tt>{washed colors}」、シャープ「@<tt>{sharp}」、ドラマチックライティング「@<tt>{dramatic lighting}」、美しい「@<tt>{beautiful}」、ポストプロセス「@<tt>{post processing}」、今日の写真「@<tt>{picture of the day}」、環境照明「@<tt>{ambient lighting}」、叙事詩的構図「@<tt>{epic composition}」……。


==== 5. まとめ
プロンプトエンジニアリングは、画像がどのように見えるかをよりよく制御することができます。
（正しい方法で行えば）あらゆる面で画質が向上します。
（こちらは原作の翻訳ですが）もしこのガイドの改善があれば、ぜひdiscord（Graverman#0804）で教えてください。


=== 各パラメータの違いを試してみる

さて、プロンプトエンジニアリングについては前節の公式ガイドの翻訳で割愛するとして、
Dream Studio 各パラメータはどのような意味を持つのでしょうか。
Cfg Scaleを最大値20（=揺らぎなし） にして、Stepsを最小の 10 から、デフォルトの 50, 最大の 150に変化して、2種類のプロンプトで観察したいと思います。

//image[StableDiffusion_Params][Dream Studio : Steps のみ変更して画像の違いを確認（上：Galaxy／下：Miku）]{
//}

他は全て同じパラメータ, Seed = 1457915964。


 * 【Galaxy】「@<tt>{A dream of a distant galaxy, by Caspar David Friedrich, matte painting trending on artstation HQ}」(起動時のデフォルト)
Stepsが増えると細部の描写が細かくなる。画の派手さ（星の輝き）は減る、脚の本数や山の描写は謎。

 * 【Miku】「@<tt>{Dancing Hatsune Miku in Minecraft Trending on pixiv HQ}」
Stepsが少なすぎるとボケ過ぎ。右上のハートはなぜ生まれたのか?


//image[StableDiffusion_Samplers][Dream Studio : サンプラーの変更は目立った違いはなさそう]{
//}

同様にサンプラーも変更してみましたが、この条件｛Cfg Scale = 20, Steps = 50, Number of Images = 1, Seed = 1457915964 ｝では違いは判りませんでした。

=== おまけ：Stable Diffusion を 手元で動かしたい

せっかく無料で使える Stable Diffusion です。Dream Studio のような有料のUIではなく、Google Colaboratory を使って無料の Python 環境で利用してみたいと思います。

必要になるのはこれらのURLです。

 * https://colab.research.google.com/
 * https://huggingface.co/spaces/stabilityai/stable-diffusion
 * https://huggingface.co/CompVis/stable-diffusion-v1-4

HuggingFaceにおいて、CompVisの Stable Diffusion v1-4 データセット(Model Card)を無償で使うことができます。

==== Stable Diffusion v1-4 ライセンス 

CreativeML OpenRAIL Mライセンスは、BigScienceとRAIL Initiativeが責任あるAIライセンスの領域で共同で行っている作業から適応された、OpenRAIL Mライセンスです。
私たちのライセンスのベースとなった BLOOM Open RAILライセンスについての記事もご覧ください。

==== モデルの説明
テキストプロンプトに基づく画像の生成・修正に利用できるモデルです。
Imagenの論文で提案されているように、事前に学習した固定テキストエンコーダー（CLIP ViT-L/14）を使用する潜在拡散モデルです。


==== 制限事項とバイアス
【制限事項】

 * 完全なフォトリアリズムを実現するものではない。
 * 読みやすいテキストをレンダリングすることができない。
 * 「青い球の上に赤い立方体が乗っている」ような、合成を伴う難しいタスクではうまく動作しない。
 * 顔や人物全般が適切に生成されない場合がある。
 * このモデルは主に英語のキャプションで学習させたので、他の言語ではうまく動作しない。
 * モデルのオートエンコーダ部分はロッシーです（lossy＝データ失われる）。
 * このモデルはアダルトコンテンツを含む大規模データセットLAION-5Bで学習させたもので、追加の安全機構や考慮なしに製品使用するには適しません。
 * データセットの重複排除のための追加的な手段は用いていません。つまり学習データで重複している画像について、ある程度の重複記憶が観察されています。
学習データは、https://rom1504.github.io/clip-retrieval/ 重複記憶された画像の検出を追跡検索することができます。


【バイアス】

画像生成モデルの性能は素晴らしいものですが、社会的バイアスを強化したり悪化させたりする可能性もあります。Stable Diffusion v1は、主に英語表記に限定された画像からなるLAION-2B(en)のサブセットで学習されました。他の言語を使用するコミュニティや文化からのテキストや画像は、十分に説明されていない可能性があります。これは西洋文化がデフォルトとして設定されることが多いため、モデル全体の出力に影響を及ぼします。さらに、英語以外のプロンプトを使用した場合のモデルのコンテンツ生成能力は、英語のプロンプトを使用した場合よりも著しく劣ります。


==== Stable Diffusion を Google Colab で動かすサンプル

詳細は、上記のマニュアルを読んでいただければよいと思いますが、試せるサンプルコードを紹介しておきます。
実際の Colab でのコードブロックは丸コピではなく、ステップごとに入力して確認していくことをお勧めします。

//list[Stable Diffusion][Stable Diffusion を Google Colab で動かすサンプル][Python]{
# インストール
!pip install --upgrade diffusers transformers scipy
# https://huggingface.co/CompVis/stable-diffusion-v1-4 利用規約に同意が必要
# HuggingFaceでアカウントを作ってトークンを取得して、張り付ける
!huggingface-cli login
# トークンの保存
!git config --global credential.helper store
import torch
from diffusers import StableDiffusionPipeline
pipe = StableDiffusionPipeline.from_pretrained("CompVis/stable-diffusion-v1-4", 
                                               revision="fp16", 
                                               torch_dtype=torch.float16,
                                               use_auth_token=True)  
pipe = pipe.to("cuda")
# ここから先は自分の使いやすいように書き換えてください
import os
import datetime
# 乱数のシード値。自分は Dream Studio からもってきます。
seed = 1317567826
generator = torch.Generator("cuda").manual_seed(seed)
# プロンプト。
prompt = "playing hatsune miku in minecraft trending on Pixiv HQ"
# 保存場所。Google Driveが使えます。使いやすいディレクトリを作って指定。
path = f"/content/drive/MyDrive/StableDiffusion/"
with torch.autocast("cuda"):
  image = pipe(prompt, generator=generator)["sample"][0]

# 画像を保存する（もっと上手に書いていいです）
is_file = os.path.isfile(path+prompt+".png")
if is_file:
    d = datetime.datetime.now().strftime('%Y-%m-%d-%H%M%S')
    image.save(path+d+" - "+str(seed)+" "+prompt+".png")
else:
    image.save(path+str(seed)+" " +prompt+".png")
//}

試しにランダムシードを同じ値にして結果の違いを比較してみました。
Dream Studioのシード値からイイ感じに出力できたプロンプト文字列を使って、上記のコードで、同じシード値を使って生成してみます。
理論上同じような画像が生成されれば大成功…！

//image[StableDiffusion_Colab][Dream Studio と Colab で同じシードから探求できるようになった]{
//}


Google Colalbo上で特徴だけを残して探究するパイプラインができた…！
これでDream Studioより使いやすく、探求コストを下げつつ画質向上できる…。
そしてシード値がかわいい…！（へへへんたいだ……！？）



=== Diffusion モデルの謎と可能性
ところで Stable Diffusion の Diffusionモデル、「なぜこのガウスノイズの除去で画像が生成されるのか？」という点については、別途研究されていて、わかっていないことも多かったようです。

Diffusionモデルはガウスノイズを追加して画像を劣化させる処理と、そのノイズを除去する処理の繰り返しによって成立しています。
この工程はランジュバン方程式 (Langevin equation) というブラウン運動の説明にも使われる確率微分方程式で説明されていますが、このノイズ追加工程は「正規分布に従うノイズ以外」でも動作することが報告されています。
例えば Cold Diffusion モデル@<fn>{ColdDiffusion}です。正規分布に従うガウスノイズでしか動作しないはずの Diffusion モデルが、ImageNet-C というブラーや降雪など各種のノイズを加えたデータセットでも動作することが確認されています。

完全なガウスノイズからヒントだけで画像が生成できるのだから、もう驚くことはないかもしれませんが、
そもそも、Diffusionモデルがランダムな拡散である必要すらない可能性もあるということで、
より制御された絵作りに利用できるだけでなく、ボカシやモザイクの除去などにも影響がある話ですし、(これは筆者の空想ですが)それらの隠蔽処理のもっともらしい復元において、任意の画像を差し込むことすらできる可能性があります。

//image[StableDiffusion_ColdDiffusion][Cold Diffusion を書いた Tom Goldstein 先生の論文紹介ツイートより。ノイズ付加、ブラー以外に、雪やアニマル化が加えられているにもかかわらず逆工程で復元できている。 https://twitter.com/tomgoldsteincs/status/1562503869984559104]

//footnote[ColdDiffusion][Cold Diffusion: Inverting Arbitrary Image Transforms Without Noise, https://arxiv.org/abs/2208.09392]

== 結論：人気絵師になって分かったこと

AI画像生成で人気絵師になるまでの流れを紹介します。
もちろんみなさんそれぞれの物語があっていいと思います。

=== まずはミュシャ風の少女画を描いて表現を探ってみた

まずは人気絵師になる初手として、アルフォンス・ミュシャ「@<tt>{by Alfons Maria Mucha}」もしくは「@<tt>{Mucha}」を追加してみました。
ミュシャは20世紀初頭に活躍したアール・ヌーヴォーを代表するチェコ出身のフランスの画家で、多くのポスター、装飾パネル、カレンダー等を制作しました。
イラストレーションとデザインの両面で日本のグラフィックデザインには大きな影響を与えています。
ミュシャの作品は星、宝石、花、植物などの様々な概念を女性の姿を用いて表現するスタイルと、背景に華麗なステンドグラスのフレームような曲線を多用したフレームのようなデザインが特徴です。

これによって人に好まれる絵を作る基本を学んでいきました。
前述の公式ガイドの通り、対象，スタイル，アーティスト，仕上げを選んでいきますが、ミュシャはレイアウトやポージングに影響がありますが、画風は何も指定しないとミュシャのグラフィックアートっぽくなります。仕上げに有効なウェブサイトを探し出すのが大事であることを学びます。

=== 「実在しないフィギュア」シリーズが人気になる

筆者が見つけた ArtStation 以外のオススメの「@<tt>{trending on}」は、「@<tt>{pixiv}」と「@<tt>{figma}」です。
「pixivも学習してるんだ、すごいな！」という感動もありました。それ以上に「@<tt>{figma}」に至っては以下の2つのサイトがあるのですが、きっちりフィギュアのほうが学習されています。

 * コラボレーションインターフェイスデザインツール「Figma」 https://www.figma.com/
 * マックスファクトリー可動アクションフィギュアシリーズ「figma」　https://www.figma.jp/ 

//image[StableDiffusion_Figma][実在しないフィギュア「Chibi Zombie Fighters」]{
//}

「実在しないフィギュア」のシリーズが（筆者の予想に反して）人気でした。
特に、ガンダムやセーラームーン、初音ミクといった、異世界コラボフィギュアがかんたんに作れてしまうのがインパクトがあります。
「Gundamiku」（ガンダム feat.初音ミク）というポップアートの権化みたいなプラモを作っていたら結構人気になりましたが、
これは、同人誌とはいえ割愛したいと思います（ pixiv 上で探してみてください！）。

そろそろプロンプトの著作性が上がっていきます。テクニック的にあまり広く教えたくはなくなり、広く教えることで、不利益があることを感じ始めます。

=== 不可能な絵を描いてみる

不可能な絵を書いてみる挑戦を始めます。
演出のためのブラーや光、フォーカスなども指定したりするようになります。
「@<tt>{focus blur}」，「@<tt>{pastel}」など、新しい仕上げを見つけると徹夜になります。

「歴史上存在しない絵」としては、「北斎風新幹線」などは「@<tt>{Shinkansen by hokusai}」で描けます。
しかし「人類がまだ描いたことがない絵」は描けるでしょうか、具体的には先史時代、人類最初期の壁画であるラスコー洞窟に初音ミクを描いてみる挑戦をしました。
呪文としては以下のような感じになります。

 * @<tt>{"Illustrated brown black Hatsune Miku is dancing with deer and ox in galaxy, by "Grotte de Lascaux", aged prehistoric wall painting strong paint brush yellow, brown, black. trending on national geographic, wide camera"}


//image[StableDiffusion_Lascaux][ラスコー洞窟に描かれた初音ミク]{
//}

「初音ミクが鹿や牛と一緒に銀河系で踊っているイラストの茶色と黒、『ラスコー洞窟』による先史時代の壁画で、黄色、茶色、黒の強い絵筆を使用！」といった、翻訳をすると中二病風味な呪文で、趣深い深いグラフィックデザインが生成されることに違和感がなくなっていきます。

しかし Stable Diffusion にどんなプロンプトを与えられるかについては、考古学的知識が必要ですし、やはり生み出されたノイズ画像から、目的の画像をゴールとして取り出すのは、我々人類なのだなという勉強不足を感じたりもします。

「不可能そうな絵」が本当に不可能なのか、考古学的視点や、真偽性はともかく、その画像が人々にとってどんな魅力や意味を持つのか……我々人類は、メディアと芸術に対して、より真剣に考えていく機会を得た感じがしてきます。

また他のAI神絵師がプロンプトを公開しているときに「@<tt>{beautiful}」といった美を表す形容語を発見すると『美しい絵を表現するために“beautiful”と表現してしまうとは浅いな……』などと芸術の先生みたいなことを心に感じてしまいます（実際には @<tt>{beautiful} はそこそこ有効なプロンプトだと思います）。

=== レタッチテクニックを学ぶ

理想を言えばAI生成一発で、そのまま pixiv に投稿できるといいのですが、運に任せるよりは、少しでも見込みがある画像が生成されたら保存してレタッチをしたほうが良いと思うようになります。

具体的は「指と顔」です。
特に指は関節数も多く、中々制御が効きません。おそらく指の学習データセットが足りないのでしょうね。
例えば「指ハートを作って」といったトレンドに乗った絵を作るのがとても難しいばかりでなく、指が6本になったり、腕が3本になったりすることはよくあります。

技術的には DALL-E2 の生成画像編集や img2img 等を使って画像から教え込んであげる、といった方法がありますが、
お手軽には Photoshop を使って消してあげるのが良いと思います。
例えば先述の「figmaで人気の」ですが、『自分がそのプラモを撮影するならこういう効果を入れるだろうなあ…』というエフェクトは加えていくとよいと思います。

色調整もいれます。
「神々しい表現」意外と西洋美術が好きそうな宗教画とかのスタイルはたくさんあるので、そこから色調整を入れて、和洋折衷で新しい表現演出をAIとのコラボで開拓していきましょう。

=== タイトルはとても大事

いくら簡単に生成できるからといって、プロンプトをそのまま画像のタイトルにして pixiv にアップロードすると、非常に良くない感じがします。
具体的は指摘しませんが「性癖丸出しのタイトル」がズラリと並ぶことになります。

人間の絵師らしく、詩的なタイトルをつける技術が磨かれていきます。
難しい表情が表現できた「ちょっとこわいけど怖くない」、「まどろみ」、「ひるねするおくさん」などなど。
スタイルだけが作品になる場合は「無題」、「習作」などとすると、雰囲気が出ます。

さらにリアルタイムでトレンドに乗っていくスキルも獲得されます。
例えば金曜ロードショーのような人気番組を見ながら、リアルタイムで画像生成をすることもAI神絵師の速度を活かした人気になる方法かもしれません。
「耳をすませば」を見ながら描いた「帰ってこないあのひと」、「雫はバイオリンを奏でたい」などを制作してみました。


=== 人気絵師は大変だ

//image[StableDiffusion_Pixiv20220905][筆者の pixiv アクセス状況。みなさまにご高覧頂き本当にありがとうございます。]

さてAI画像生成を使って人気絵師になってはみたものの、これが意外と大変でした。

pixiv の通知は鳴りやみません。自分で手で描いた時は、何時間かかって描いた新作も30秒ぐらいで「新作リスト」から消えて行ってしましますから、それに比べれば幸せでしょう。
しかも意外と意外な作品に「いいね！」や「ブックマーク」がつきます。
最初のうちは楽しく観ていたのですが、なんというか……。
何が大変って、「人の期待と性癖」を毎日こすりつけられるのです。
これに日々耐えてる絵師さんってほんとうにすごい

「おもしろいだろうな」という気持ちで描いても、「自分はそのジャンル極めたくない」と気付いてしまうこともあります。

「描きたいものを描く」のと「求められて描く」のは異質なものです。
特に「初音ミク」は人気です。
例えば「ミク × ガンダムコラボ」が需要あることはわかりました。

でもそれだけでは描き続けられません。
スタイルは「大河原邦男」だろうか？カトキハジメだろうか？出渕裕だろうか？
そういう名前が付いたスタイルとして指定できるならいいのですが、そこまでの日本人作家は滅多にいません。
そういう意味では Hokusai や Miku はすごい。文字数に対する情報量からすれば Picaso よりもすごいかもしれない。

でも「Gundamiku」シリーズをバンダイさんやクリプトンさんやその他の著作権者さんやそのファンの皆さんに攻撃されてまで作る必要はないですよね。
ある程度良作のコンセプト画像ができれば、あとはプロの方が作ったほうが良いと思います。

特に「自由に書いて/描いてよい」ではなく、「細かい指定があるお客さん」の依頼を受けるような例はとても大変だと思います。
Photoshopでちょっと描き足せばいいような修正ならともかく、『背景にこういうロゴを入れてほしい』といったリクエストはまず無理だと思います。
まあこれは「人間の絵師さんでも同じだ」と思うかもしれないのですが、『どうせ呪文で何でも描けるんでしょ？』という視点に立たれると、より大変だと思います。


=== 「AI神絵師」はコスト的に見合うのか？

「AI神絵師」はコスト的に見合うのでしょうか。

そもそも MidJourney や Dream Studio といったAI画像生成サービスに支払っている計算機コストを上回るような、ファンからのお布施が入ってこなければ「職業：神絵師」が成立しないと思います。
手元で Python環境やGPU演算環境をつくれば少しは安くなるのかもしれないですが、それでもお客さんから10円でもお金をもらうっていうのは大変なことです。

 * 執筆時点の結論：ガチャのイラストを描く絵師さんはすごい。

とはいえ、商品性を学習させていくと、すぐに状況はアップデートされる気もします。
たとえば顔アイコンやLINEスタンプなどは学習しやすいかもしれない。商品性をアノテーションしてくことで……というところで、8月29日に「Mimic」なる、画風を獲得してAI画像生成モデルを作るサービスがリリースされました。実際触ってみたのですが、Diffusionモデルですね、よくできていると思います。
そして、イラストファンから攻撃されているムーブを見かけました。


===  #StableDiffusion が禁止タグに設定される未来
「思い通りの絵を一通り描けるようになる」をマスターすると、 次は「Pixivが #StableDiffusion を禁止タグに設定する未来」が見えてきました。

えっちな画像を安易に大量生成して、性癖丸出しのタイトルとともに、比較的クオリティの高い絵をpixivのタイムラインに乗せる人が大量に出てくる未来がみえてきます。そもそもpixivでは「オリジナル画像」というチェックボックスがあるのですが、Stable Diffusionを使って書いた絵が「オリジナルではない」という主張をするのは難しいと思います。

そもそも「二次創作である」とすると、「○○の二次創作です」という主張をすることで「○○が好きな人」に刺さるという構造がありますが、「二次創作ではない、これは（○○がいいな！と思って）インスピレーションを受けたが、オリジナルを目指している」という「オリジナル」はいくらでもあるし、Stable Diffusionにおいては潜在変数の組み合わせでしかないでしょう。

簡単に表現すれば「人類の美学とモラルが問われている」という1行でしかないのですが。
具体的には「人間が手を動かして描いた絵以外は認めない！」という原理主義の絵師さんと、そのファンの方々、そして「え？ツールとして使うかどうかとか含めて技量では」という革新主義の方々の認識の違い。さらに、絵を描く側の意志とは全く関係なく、勝手に入手した画像からモデルを獲得しようとする方々などなど。

似たような問題は今後リリースされるサービス全てについて言えると思います、また日本のこの分野においては、勝手に善悪のラインを引いて警察行為を行う人もいるので、どのあたりにモラルラインが引かれるのかは興味深い点ではあります。




=== 日本の法律とAI神絵師の適法性

本原稿執筆時点で前述のまだ炎上がやむ気配がないので、あえて法律の解説も書き添えておきます。

『AIを生成するために他人の画像や文章などの著作物を勝手に収集して利用することは著作権法上問題なのではないか』という議論について、
AI神絵師の適法性を考えることで、日本のこの分野における法整備環境を学ぶことができます。
日本国内ではまず日本の著作権法と「AI・データの利用に関する契約ガイドライン 1.1版」（経済産業省）@<fn>{AIDATA}について知っておくとよいと思います。

日本の著作権法には「著作者本人の権利」として「著作財産権」と「著作者人格権」があります。
著作財産権は、著作者の財布を守る権利で、複製権と翻案権があります。
そして著作者人格権 (Moral rights) は、著作者の心を守る権利です。
公表権、氏名表示権、同一性保持権、名誉声望保持権、出版権廃絶請求権、修正増減請求権などがありますが
「著作者が精神的に傷つけられない権利の総称」と説明することができます。
著作者だけが持っている権利で、譲渡したり、相続したりすることはできません。 

譲渡、相続、貸与できる著作財産権に対して、著作者人格権は譲渡が認められていません。
これは著作者人格権が著作者本人の心を保護することを目的としているためです。
また著作者ではない「神絵師のファン」が、「こうあってほしい」という権利を主張することもできません(感情的にはわからないでもないですが)。

なお複製権や出版権などの著作財産権を第三者に売却した後でも、著作者人格権だけは消滅せず著作者本人を守り続けることになります（これを「一身専属性」と呼びます）。
この一身専属性を著作者本人の意志で否定する、つまり著作者人格権を自ら放棄したり、不行使にする契約を結べるのかについては、国によって定義や対応が大きく異なります。

著作権の管轄である文化庁による解説では、著作者の本人の意思に関わらず、
「例えば人工知能の開発のための学習用データとして著作物をデータベースに記録する行為など、広く著作物に表現された思想又は感情の享受を目的としない行為等を権利者の許諾なく行える」と具体的に記載されています@<fn>{Houkaisei}。

そもそも日本の著作権法には（国際条約であるベルヌ条約と同様）「著作者人格権の放棄」は規定がないのですが、
もともと著作権法では、一定の｢例外的｣な場合に著作権等を制限して、著作権者等に許諾を得ることなく利用できることを定めています（第30条〜第47条の8）@<fn>[jiyu]。
具体的には著作権法 第47条の7「著作権法情報解析のための複製等」として
「コンピュータ等を用いて情報解析を行うことを目的とする場合には、必要と認められる限度において記録媒体に著作物を複製・翻案することができる」と定められています。

さらに最新の法律では、平成30年(2018)月18日に成立した 改正著作権法第 30 条 の4 において
「著作物に表現された思想又は感情を自ら享受し又は他人に享受させることを目的としない場合には、その必要と認められる限度において、権利者の利益を通常害さないと評価できる」と明確に規定されました。

「情報解析」のためであれば、商用／非商用、テキストや引用に限らず、広い範囲で著作物の利用を認める……というこの条文は、世界的に見るとかなり特殊であるそうです。
特に「目的の限定」がないため、営利企業が営利目的で情報解析を行う場合にもこの条文が適用でき、これによって特殊性がうまれています。

新たなAI利用サービスやAI画像生成、利用規約の構築や、より具体的な法律上の論点については、弁護士など法律の専門家に相談するとよいと思います。
よくまとまっているブログ記事として「Midjourney、Stable Diffusion、mimicなどの画像自動生成AIと著作権」（2022/08/31 柿沼太一）を引用しておきます@<fn>{Kakinuma}。

//footnote[AIDATA][https://www.meti.go.jp/press/2019/12/20191209001/20191209001.html]
//footnote[jiyu][(文化庁) 著作物が自由に使える場合, https://www.bunka.go.jp/seisaku/chosakuken/seidokaisetsu/gaiyo/chosakubutsu_jiyu.html]
//footnote[Houkaisei][著作権法の一部を改正する法律（平成30年法律第30号）について, https://www.bunka.go.jp/seisaku/chosakuken/hokaisei/h30_hokaisei/]
//footnote[Kakinuma][Midjourney、Stable Diffusion、mimicなどの画像自動生成AIと著作権, https://storialaw.jp/blog/8820]

=== SNS時代のアマチュア画家にとってAI神絵師とは何なのか

問題は「上手い」とか「下手」とか、人間は美醜に対して真剣になればなるほど「美しさに対して不寛容である」という点です。
アマチュアがソロで描いているだけであれば、描いている本人がよければそれでいいのですが、SNS時代においては、

 1. 本人が好きで描いているのであればそれでいい
 2. 上手い人が視界に入る
 3. 自分の絵が恥ずかしくなる
 
…といったサイクルに常に晒されます。
これは実はSNS時代に限ったことではなく、同人誌時代も同じことですし、昭和の時代の漫画家であれば、雑誌や投稿の上で戦っていました。このステップには続きがあります。

 1. 本人が好きで描いているのであればそれでいい
 2. 上手い人が視界に入る
 3. 自分の絵が恥ずかしくなる （ここで折れてしまう人もいるのですが）
 4. うまい人の絵をみて学ぶ

…というスイッチが重要かもしれません。
「この人うまい！」と思うだけならいくらでもいるのですが、「ああ！こういう表現があったか、こういう構図、こういうシチュエーション、こういう描線…この瞳はどうやって描いているのだろう…？」といった探求心と向上心がジェラシーよりも上回ることが大切だと思います。
単に上手な絵を蒐集している人と、手を動かして描いている人の違いはそこにあるかもしれませんし、その2者の違いはとても大きいです。

そしてこのプロセスはAI神絵師にとってもなんら変わりません。
いいプロンプトがあれば盗む、これは今までの漫画やイラストの世界の技術で「描く技術を盗む」そのマインドと何ら変わらないかもしれません。

（良いか悪いか、ではなく、そういう性質のものだということです）

そして、冒頭のこういう感想を抱くのです。

> Stable Diffisuionで描いた絵をpixivにアップロードした瞬間に画風を見抜いておすすめタグを提案してくるんだけど、潜在変数とエンコーダとデコーダーの合間で絵を描いている感はんぱない。

沢山のAI神絵師が登場し、高品質の絵を見せつけられ続ける中で、モチベーションを高く維持し続けられるもののみがその街道を走り続けられます。


=== 「萌え絵を書いてください」というお願いの今後

本稿が示した通り、「萌え絵を書いてください」というお願いは比較的短期間に獲得可能であり、猥褻図画もしくはそれに準じる画像をひたすら蒐集・消費したいという目的のサイクルは確実な需要がある一方で、ある程度分離、カテゴライズ、カーテンなりR-18なりで別けることで双方に健全な進化成長を促すことができるようにも思います。

またメディア芸術史的な視点でStable Diffusionを観察すると、日本のマンガ、アニメーションやゲームイラストに出てくるモチーフは、比較的記号化が進んでしまう要素であるという体感もあります。
具体的には表情演技です。でもこれは解決する気もします。
むしろ、コンテンポラリーダンスや、格闘技のような分野のデータセットが出てくると、より表現力も上がるように思いますし、既存の格闘ゲームで生成されているような画像から学習すると、「竜巻旋風脚を総理大臣に」といった画像も簡単に生成できる時代が来てしまいます。

ところでここ数日、AI神絵師として実験を行っている間、描き手、クリエイターとしての感覚として、自分の画力や筋力（気合の入った絵を何時間も高速に描き続けるには筋力が必要です）に関係なく、新しいスタイルの発見や、上手な出力ができるようになると「脳が発火している」を感じました。

つまり人間の脳は絵を描きたい。表現したい、表現を探求したい。これは単体の脳でも感じます。それを脳の外に画像として放出することで、他者の評価や需要を満たす、そしてもっと上手にAIを使いこなす人々にジェラシーを描いたり、その技術を獲得するためにお金を払ったりする人も出てくると思います。

このサイクルであることは全く否定できません。もちろんこのサイクルに Stable Diffusion というアルゴリズムや関連のサービスが入ってきました。技術の思想はDALL-Eを産んだOpenAIが「企業の独占ではなく」という立ち位置で生まれていることからも、単一企業の独占ではありませんが、賢い投資家たちは「人類が脳汁を発したり、お金を出してでも手に入れたいと思うもの」に対して投資行動をしていくと思います。規模の大小はわかりませんが、これからもAI画像生成技術には一定の注目があると思います。

本稿では、CLIP や GLIDE そして 超解像技術を用いたノイズ除去拡散確率モデル条件付き画像生成を一気に解説しました。
その中で、文字列から表現できる潜在変数の組み合わせが、プロンプトであり、エンジニアリング要素でもあります。

もちろん本稿で扱わなかった手法で word2vec や 領域指定、img2img など、新しい方法、特に従来の文字で入力する言語以外の方法はたくさん出てくると思います。
Stable Diffusion にはDALL-E2にあったような「任意の場所を描きなおす」というプロセスはないようです。
実際に、これらの絵作り工程では、ポージングやレイアウトを直接指定したいことはたくさんありますし、いちばん難しいところは「指と顔の表情」の指定です。顔は記号的な表現でよければワードで指定できるとは思います。でも絵画で表現したいような複雑な表情は難しいですし、これを言語で表せるならそれこそ絵画の終わりを感じる気もします。またアニメーションで表現したい動的な表情変化、表演技に特化した対話的なUIなどもあるかなと思います。この辺はCGxAI分野の研究者のネタでしかないので、学会などでお話しできればなと思います。

逆を言えば、
潜在変数の組み合わせをどのように詠唱させたか？という点では、実際の絵のデッサンでいえば、エンピツの削り方、その鉛筆を制御する筋肉の鍛え方、光の捉え方、面や空間の捉え方…そしてデジタルイラストレーションでいえば、構図、彩色、表情などに現れてきます。どれだけ多くのスタイルを知っているか？これは美術史なり、美術書なりを読んでいる人のほうが有利です。日本語ではなく英語で指定したほうが良いですし、ベクトル空間として表現可能な画風を英語で指定できさえすればよいので、有効なキーワードを知っていることが実力となるでしょう。

むしろここを人間と対話的に学習させるインタフェースなども需要が出てきそうです。word2vecのようなベクトルの演算でも表現可能です。
つまり「AIが美しい絵を描くなら人類は絵を学ばなくていいか」という命題は、「学ぶ必要がある」ということであり、もはやPythonを用いた数学や統計学も芸術の一端をになっているかもしれません。
「描かなくていいか」は実際の絵の具やデジタルイラストレーションの過程と同じように「必要があれば道具として使ったり学んだりすればいい」という事になるかと思います。



== まとめ：筆をおく前に

=== 人工知能とともに絵を描くという行為が人類にどんな影響を与えているか？

絵を描く必要があるかどうか？学ぶ必要があるかどうか？については実際に体験して本気で画像を作ってみるとわかることがあると思います。そこには明確な技量が必要であり、若い人や経験がある人にとっても、一度は体験しておくべき衝撃があると思います。そしてそれは、「エンピツをもって絵を描くことの意味」とほぼ同意ではないでしょうか。つまり「その技法で頑張ること」の意味を自分が理解すれば、それにこだわる必要はないが、やったことがない状態で良し悪しを判断するのは野蛮なことである、というぐらいの話でしょうか。もちろん「苦労したほうが良いものが描ける」という視点もあると思いますが、技法としての苦労と、表現としての苦労、表現者の表現したい画風とはそれぞれ異なってよいという見方ができるかどうかです。単体の脳にとって、美的な何かを探求する、自らのモチベーションと向き合う、という行為は大変刺激のある行為であり、数億～数十億といった、現在の地球人類の個体数の総和に匹敵する数のスタイルを学習したAIと対話することの意味は、まさに人類がいままで描き残してきた画像メディアの歴史的集約との対話を行っていることに他ありません。神絵師との対話は「こういう画像を得たい」という人間のモチベーションと向き合うことに他ありません。むしろ人類が「画像などいらぬ」という存在であれば、AIアルゴリズムやそれを開発する企業、新しいスタイルを収集して学習させるオペレーターは不要です。人間の欲望、無垢な想像力と向き合っていく必要があります。例えば日本語入力IMEのような、予測変換やUI技術を駆使した日本語文字入力技術がなければ、我々日本人はまともに文章を書くことすら難しいでしょう。そのような技術をなくして、小中高校のような鉛筆がなければ書けない日本語のみを「日本語」とすることはとても乱暴で、それすらも「鉛筆やノート」という工業製品がなければ成立していません。


=== 近代史から想像する「絵を描くこと」と技術の関係

私は写真からバーチャルリアリティに入った人間なのですが、そういえば印象派画派は写真機の誕生によって生まれているという美術史観もありますね。
古くはルネサンス時代のレオナルド・ダヴィンチの遠近法や17世紀のフェルメールは遠近法に、ピンホールカメラの物理を使ったカメラ・オブスキュラを使っています。
さらに写真の発明、特にネガポジ方式である「カロタイプ（calotype）」が発明されたは1841年以降は、写真を容易に複製し、拡大縮小もできるようになりました。

その19世紀、印象派画家は写真から新たな創作意欲を刺激されたています。写真機の登場によって肖像画を描く市場価値は大きく下がっていたのかもしれません。
画家たちは、それまでのようにスタジオに籠ってランプの光で歴史的な絵画や肖像画を製作するのではなく、日常的なモチーフを屋外に出て自然光の下で絵を描くことに興味を持ち始めます。

ただし当時の画家たちはパレット上で顔料と油を混ぜて絵の具を作ってから製作に取り掛かる必要があったため、スタジオの外で絵を描くことは実質的に不可能でした。
チューブ絵の具が発明されたのは写真機が登場した1841年です。
そしてルノワールは「チューブ絵の具が発明されなかったら印象派も生まれなかった」と言っているそうです。

人類のやることはまだまだありそうです。
そして人工知能で絵を描く以外にも、作文を書くツールなども生まれています。
そうこの原稿も、ツールで書いているかもしれません
（手で執筆しています、そして最後の最後まで脱稿できてなくてごめんなさい＞部員各位）。


　　　2022年8月31日 初音ミクの15回目の17歳の誕生日にて 白井暁彦

#@# https://wiis.info/blog/photography-and-impressionism/

//footnote[tweet0824][https://twitter.com/o_ob/status/1562248466490748928]
//footnote[GLIDE][https://github.com/openai/glide-text2im]
//footnote[GLIDE-Paper][GLIDE: Towards Photorealistic Image Generation and Editing with Text-Guided Diffusion Models, https://arxiv.org/abs/2112.10741]
//footnote[LAION][https://github.com/LAION-AI/laion-datasets/blob/main/laion-aesthetic.md]
